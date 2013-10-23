/**
 * Runs a hunter's game turn, limiting the execution time
 * and saving their best plays (registerBestPlay)
 *
 * Takes in JSON:
 * { "pastPlays": "...", "messages": ["messageHere", ...] }
 * over STDIN
 * to build the HunterView
 *
 * and outputs JSON:
 * { "move": "..", "message": "myMessage" }
 * over STDOUT
 * either:
 *  - decideMove finishes
 *  or
 *  - a timeout occurs
 * (in both situations the program exits after outputting)
 *
 * also outputs any STDOUT or STDERR made by the hunter over STDERR
 *
 *
 * David Collien
 * 2012
 *
 * Compiles with:
 *  gcc -o myPlayer game.c hunter.c HunterView.c -ljansson
 * and any other player's files
 * (requires the jansson library: http://www.digip.org/jansson/)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#include <sys/time.h>

#include <jansson.h>

#include "game.h"
#include "HunterView.h"
#include "hunter.h"


#define USEC_TO_SEC 1000000

// convert milliseconds into seconds component
#define LIMIT_SEC (LIMIT_LIMIT_MSECS/1000)

// extract milliseconds component and convert to microseconds
#define LIMIT_USEC ((LIMIT_LIMIT_MSECS%1000) * 1000)

// moves given by registerBestPlay are this long (including terminator)
#define MOVE_SIZE 3

// Options here include:
//   SIGVTALRM, ITIMER_VIRTUAL
//     limit the hunter's processing time (CPU seconds)
//
//   SIGPROF, ITIMER_PROF
//     limit the hunter's system time
//     (processing + anything system needs to do to run the hunter)
//
//   SIGALRM, ITIMER_REAL
//     real-world seconds over all currently running processes
//
#define TIMER_SIGNAL SIGPROF
#define TIMER_TYPE ITIMER_PROF

// stores input data
typedef struct {
   char *pastPlays;
   playerMessage *messages;
   int messagesLength;
} inputData_t;

static inputData_t *getInput( void );
static void outputMove( void );
static void startTimer( void );
static void timesUpHandler( int signalID );
static void freeInput( inputData_t *inputData );

// The minimum static globals I can get away with
static struct timeval startTime;
static struct timeval endTime;
static bool isTiming = false;
static char latestPlay[MOVE_SIZE] = "";
static char latestMessage[MESSAGE_SIZE] = "";
static int fd;
static fpos_t pos;

int main( int argc, char *argv[] ) {
   HunterView gameState;
   
   inputData_t *inputData;
   no_stdout_for_you();
   
   // we're using stdout for move output
   // user's stdout is redirected to stderr
   
   inputData = getInput( );
   gettimeofday(&startTime, NULL);
   // start timer and enable timeUpHandler interrupt
   startTimer( );
   
   gameState = newHunterView( inputData->pastPlays, inputData->messages );
   decideMove( gameState );
   disposeHunterView( gameState );
   
   // stop timing straight away after decideMove finishes
   isTiming = false;
   
   gettimeofday( &endTime, NULL );
   
   outputMove( );
   
   freeInput( inputData );
   
   return EXIT_SUCCESS;
}

void no_stdout_for_you() {
   fflush(stdout);
   fgetpos(stdout, &pos);
   fd = dup(fileno(stdout));
   dup2(fileno(stderr),fileno(stdout));
}

void stdout_for_you() {

   fflush(stdout);
   dup2(fd, fileno(stdout));
   close(fd);
   clearerr(stdout);
   fsetpos(stdout, &pos);

}

// Saves characters from play (and appends a terminator)
// and saves characters from message (and appends a terminator)
void registerBestPlay ( char *play, playerMessage message ) {
   strncpy( latestPlay, play, MOVE_SIZE-1 );
   latestPlay[MOVE_SIZE-1] = '\0';
     
   strncpy( latestMessage, message, MESSAGE_SIZE );
   latestMessage[MESSAGE_SIZE-1] = '\0';
}


// Internal functions:

// Output the last registered move as JSON
static void outputMove( void ) {
   stdout_for_you();
   double startTime_uS = startTime.tv_sec*USEC_TO_SEC + (startTime.tv_usec);
   double endTime_uS   = endTime.tv_sec*USEC_TO_SEC + (endTime.tv_usec);
   int usTaken = endTime_uS - startTime_uS;
   
   json_t *outputJSON;
   
   json_t *moveJSON;
   json_t *messageJSON;
   json_t *timerJSON;
   
   // create a new JSON Object
   outputJSON = json_object( );
   
   // create new JSON Strings from the last registered move
   moveJSON = json_string( latestPlay );
   messageJSON = json_string( latestMessage );
   
   // store them inside the JSON Object (and automatically clean references)
   json_object_set_new( outputJSON, "move", moveJSON );
   json_object_set_new( outputJSON, "message", messageJSON );
   
   
   json_object_set_new( outputJSON, "timer", json_integer( usTaken ) );
   
   json_dumpf( outputJSON, stdout, 0 );
   no_stdout_for_you();
}

// Clean up memory allocated for the input data
static void freeInput( inputData_t *inputData ) {
   free( inputData->messages );
   free( inputData->pastPlays );
   
   free( inputData );
}

// Allocate input data and get JSON from stdin
static inputData_t *getInput( void ) {
   int i = 0;
   int pastPlaysLength = 0;
   int messagesLength  = 0;
   
   inputData_t *inputData = malloc( sizeof( inputData_t ) );
   
   json_t *rootJSON;
   json_t *pastPlaysJSON;
   json_t *messagesJSON;
   
   json_t *messageItemJSON;
   
   json_error_t error;
   
   char *pastPlays;
   char *message;
   
   
   // get JSON object from STDIN
   rootJSON = json_loadf( stdin, 0, &error );
   if ( rootJSON == NULL ) {
     fprintf( stderr, "Input error: on line %d: %s\n", error.line, error.text );
     exit( EXIT_FAILURE );
   }
   
   // get past plays string from the JSON object
   pastPlaysJSON = json_object_get( rootJSON, "pastPlays" );
   if ( !json_is_string( pastPlaysJSON ) ) {
     fprintf( stderr, "Input error: pastPlays is not a string\n" );
     exit( EXIT_FAILURE );
   }
   
   pastPlays = (char *)json_string_value( pastPlaysJSON );
   pastPlaysLength = strlen( pastPlays );
   
   // allocate and copy past plays
   inputData->pastPlays = malloc( sizeof(char) * (pastPlaysLength+1) );
   strncpy( inputData->pastPlays, pastPlays, (pastPlaysLength+1) );
   inputData->pastPlays[pastPlaysLength] = '\0';
   
   // get messages array from the JSON object
   messagesJSON = json_object_get( rootJSON, "messages" );
   if ( !json_is_array( messagesJSON ) ) {
     fprintf( stderr, "Input error: messages is not an array\n" );
     exit( EXIT_FAILURE );
   }
   
   // allocate messages in struct
   messagesLength = json_array_size( messagesJSON );
   inputData->messages = malloc( sizeof(playerMessage) * messagesLength );
   inputData->messagesLength = messagesLength;
   
   for ( i = 0; i < messagesLength; i++ ) {
     messageItemJSON = json_array_get( messagesJSON, i );
     
     if ( !json_is_string( messageItemJSON ) ) {
       fprintf( stderr, "Input error: messages[%d] is not a string\n", i );
       exit( EXIT_FAILURE );
     }
     
     // copy over message string
     message = (char *)json_string_value( messageItemJSON );
     strncpy( inputData->messages[i], message, MESSAGE_SIZE );
     inputData->messages[i][MESSAGE_SIZE-1] = '\0';
   }
   
   return inputData;
}

// Start the process timer
static void startTimer( void ) {
   struct sigaction timerAction;
   struct itimerval timer;
   
   // tell it to fire the timesUpHandler interrupt
   // when TIMER_SIGNAL is received
   memset( &timerAction, 0, sizeof(timerAction) ); 
   timerAction.sa_handler = &timesUpHandler; 
   sigaction( TIMER_SIGNAL, &timerAction, NULL );
   
   // set up timer's timing time
   timer.it_value.tv_usec = LIMIT_USEC;
   timer.it_value.tv_sec = LIMIT_SEC;
   
   // don't re-fire on an interval
   timer.it_interval.tv_usec = 0;
   timer.it_interval.tv_sec = 0;
   
   // flag that we're now timing
   isTiming = true;
   
   gettimeofday( &startTime, NULL );
   
   // start your engines
   setitimer( TIMER_TYPE, &timer, NULL );
}

// This is called when the TIMER_SIGNAL is received
static void timesUpHandler( int signalID ) {
   // what to do if interrupted by timer
   if ( isTiming ) {
	  gettimeofday( &endTime, NULL );
	  outputMove( );
	  exit( EXIT_SUCCESS );
   }
}
