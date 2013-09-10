#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "game.h"
#include "HunterView.h"
#include "Stack.h"


#define FALSE 0
#define TRUE 1

//#define DEBUG

#define ENCOUNTER_NONE     0
#define ENCOUNTER_TRAP     1
#define ENCOUNTER_DRACULA  2
#define ENCOUNTER_VAMPIRE  3

#define NUM_ENCOUNTERS 4
#define MAX_ENCOUNTERS_PER_TURN 4

//TODO:
//Last known Dracula Location
//Dracula trail
//Tests


typedef struct draculaMoveData {
   int placedTrap;      
   int vampirePlaced;
   int vampireMatured;
   int trapLeftTrail;
} draculaMoveData;

typedef struct hunterEncounterData {
   int encounterType;
} hunterEncounterData;

typedef struct moveData {
   int moveNumber;
   playerCode player;
   locationCode location;
   draculaMoveData draculaMove;
   hunterEncounterData hunterEncounter[MAX_ENCOUNTERS_PER_TURN];
} moveData;

typedef struct playerInfo {
   locationCode location;
   int health;
} playerInfo;

typedef struct hunterView {
   moveData moves[MAX_MOVES_IN_GAME];
   playerInfo players[NUM_PLAYERS];
   int movesPlayed;
   int gameScore;
   char** playerMessages;
} hunterView;


static locationCode strToLocationCode(char *location);
static playerCode charToPlayerCode(char player);
#ifdef DEBUG
static void dumpMoves(HunterView hv);
#endif
static void tokenisePlayString(HunterView hv, char *playString);
static void simulateGame(HunterView hv);
static char *getPlayerName(playerCode p);
static char *getLocationName(locationCode l);
static int isSea(locationCode l);

// Constructor
HunterView newHunterView(char *pastPlays, playerMessage messages[]) {
   assert(messages);
   HunterView hv = malloc(sizeof (hunterView));
   memset(hv, 0, sizeof(hunterView));
   hv->movesPlayed = 0;
   tokenisePlayString(hv, pastPlays);
   simulateGame(hv);
#ifdef DEBUG
   dumpMoves (hv);
#endif
   
   // copy in each of the player message
   int messageIndex = 0;
   hv->playerMessages = malloc(hv->movesPlayed * sizeof(char*)); // allocate an array of strings for each item
   while (messageIndex < hv->movesPlayed) {
      char* message = malloc(MESSAGE_SIZE);
      memcpy(message, messages[messageIndex], MESSAGE_SIZE);
      hv->playerMessages[messageIndex] = message;
      
      messageIndex += 1;
   }
   
   return hv;
}

void disposeHunterView(HunterView toBeDestroyed) {
   int message = 0;
   while (message < toBeDestroyed->movesPlayed) {
      free(toBeDestroyed->playerMessages[message]);
      message += 1;
   }
   
   free(toBeDestroyed->playerMessages);
   
   free(toBeDestroyed);
}

static void simulateGame (HunterView hv) {
   int currentMove, i, j; 
   
   // starting values
   for (i = 0; i < NUM_PLAYERS; i++) {
      hv->players[i].health = GAME_START_HUNTER_LIFE_POINTS;
      hv->players[i].location = UNKNOWN_LOCATION;
   }
   hv->players[PLAYER_DRACULA].health = GAME_START_BLOOD_POINTS;
   hv->gameScore = GAME_START_SCORE;
   
   for (currentMove = 0; currentMove < hv->movesPlayed; currentMove++) {
      // DEBUG
      if (currentMove % NUM_PLAYERS == 0) {
         printf("Round: %d. Score: %d.\n", currentMove/NUM_PLAYERS, hv->gameScore);
         for (j = 0; j < NUM_PLAYERS; j++) {
            printf("  %14s %3d %s\n", getPlayerName(j), hv->players[j].health, getLocationName(hv->players[j].location));
         }
         printf("\n");
      }
      // END DEBUG
      
      locationCode oldLocation;
      moveData move = hv->moves[currentMove];
      playerInfo *currentPlayer;
      assert(move.player < NUM_PLAYERS && move.player >= 0);
      currentPlayer = &(hv->players[move.player]);
      oldLocation = currentPlayer->location;
      currentPlayer->location = move.location;
      
      if (move.player != PLAYER_DRACULA) { // hunter
         for (i = 0; i < MAX_ENCOUNTERS_PER_TURN; i++) {
            if (move.hunterEncounter[i].encounterType == ENCOUNTER_TRAP) {
               currentPlayer->health -= LIFE_LOSS_TRAP_ENCOUNTER;
            } else if (move.hunterEncounter[i].encounterType == ENCOUNTER_VAMPIRE) {
               // Nothing happens.
            } else if (move.hunterEncounter[i].encounterType == ENCOUNTER_DRACULA) {
               hv->players[PLAYER_DRACULA].health -= LIFE_LOSS_HUNTER_ENCOUNTER;
               currentPlayer->health -= LIFE_LOSS_DRACULA_ENCOUNTER;
            } else {
               assert(move.hunterEncounter[i].encounterType == ENCOUNTER_NONE);
            }
         }
         
         
         if (currentPlayer->health <= 0) {
            hv->gameScore -= SCORE_LOSS_HUNTER_HOSPITAL;
            currentPlayer->location = ST_JOSEPH_AND_ST_MARYS;
            currentPlayer->health = MAX_HUNTER_LIFE_POINTS;
         } else if (currentPlayer->location == oldLocation) {
            currentPlayer->health += LIFE_GAIN_REST;
            if (currentPlayer->health > MAX_HUNTER_LIFE_POINTS) {
               currentPlayer->health = MAX_HUNTER_LIFE_POINTS;
            }
         }
         
      } else { // dracula
         if (move.draculaMove.vampireMatured == TRUE) {
            hv->gameScore -= SCORE_LOSS_VAMPIRE_MATURES;
         }
         hv->gameScore -= SCORE_LOSS_DRACULA_TURN;
         
         if (hv->players[PLAYER_DRACULA].location == CASTLE_DRACULA ||
            hv->players[PLAYER_DRACULA].location == TELEPORT) {
            hv->players[PLAYER_DRACULA].health += LIFE_GAIN_CASTLE_DRACULA;
         }
         
         // find dracula's position for life loss at sea.
         int isAtSea = isSea(hv->players[PLAYER_DRACULA].location);
         int movesDoubledBack;
         locationCode oldLocation;
         
         if (!isAtSea && hv->players[PLAYER_DRACULA].location >= DOUBLE_BACK_1 &&
            hv->players[PLAYER_DRACULA].location <= DOUBLE_BACK_5) {
            
            movesDoubledBack = hv->players[PLAYER_DRACULA].location - DOUBLE_BACK_1 + 1;
            oldLocation = hv->moves[currentMove - (movesDoubledBack * NUM_PLAYERS)].location;
            
            if (isSea(oldLocation)) {
               isAtSea = TRUE;
            }
         }
         
         if (isAtSea) {
            hv->players[PLAYER_DRACULA].health -= LIFE_LOSS_SEA;
         }
      }
   }
}

static int isSea(locationCode l) {
   return ((l >= NORTH_SEA && l <= BLACK_SEA) || l == SEA_UNKNOWN);
}

static int isRealLocation(locationCode l) {
   return (l >= ALICANTE && l <= BLACK_SEA);
}

static void tokenisePlayString (HunterView hv, char *playString) {
   int i, j;
   int pastPlaysLength = strlen(playString);
   char locationString[3], encounterChar;
   for (i = 0; i < pastPlaysLength; i += 8) {
      moveData *currentMove = &(hv->moves[hv->movesPlayed]);
      currentMove->player = charToPlayerCode(playString[i]);
      currentMove->moveNumber = hv->movesPlayed;
      locationString[0] = playString[i + 1];
      locationString[1] = playString[i + 2];
      locationString[2] = '\0';
      currentMove->location = strToLocationCode(locationString);
      if (currentMove->player == PLAYER_DRACULA) {
         currentMove->draculaMove.placedTrap    = (playString[i + 3] == 'T');
         currentMove->draculaMove.vampirePlaced = (playString[i + 4] == 'V');
         currentMove->draculaMove.vampireMatured = (playString[i + 5] == 'V');
         currentMove->draculaMove.trapLeftTrail = (playString[i + 5] == 'M');
      } else {
         for (j = 0; j < 4; j++) {
            encounterChar = playString[i + j + 3];
            if (encounterChar == 'T') {
               currentMove->hunterEncounter[j].encounterType = ENCOUNTER_TRAP;
            } else if (encounterChar == 'V') {
               currentMove->hunterEncounter[j].encounterType = ENCOUNTER_VAMPIRE;
            } else if (encounterChar == 'D') {
               currentMove->hunterEncounter[j].encounterType = ENCOUNTER_DRACULA;
            } else if (encounterChar == '.') {
               currentMove->hunterEncounter[j].encounterType = ENCOUNTER_NONE;
            } else {
               printf("Encounter Char: %c at %d\n", encounterChar, i + j + 3);
               assert(FALSE);
            }
         }
      }
      
      hv->movesPlayed++;
   }
}

#define truthToString(x) ((x)?"True":"False")

static char *getLocationName(locationCode l) {
   
   if (l == -1) {
      return "Unknown";
   }
   assert(l < NUM_LOCATIONS && l >= 0);
   
   char *placeNames[] = {"Alicante", "Amsterdam", "Athens", "Barcelona", "Bari",
      "Belgrade", "Berlin", "Bordeaux", "Brussels", "Bucharest",
      "Budapest", "Cadiz", "Cagliari", "Castle Dracula",
      "Clermont Ferrand", "Cologne", "Constanta", "Dublin",
      "Edinburgh", "Florence", "Frankfurt", "Galatz", "Galway",
      "Geneva", "Genoa", "Granada", "Hamburg",
      "St Joseph & St Mary's", "Klausenburg", "Le Havre",
      "Leipzig", "Lisbon", "Liverpool", "London", "Madrid",
      "Manchester", "Marseilles", "Milan", "Munich", "Nantes",
      "Naples", "Nuremburg", "Paris", "Plymouth", "Prague",
      "Rome", "Salonica", "Santander", "Saragossa", "Sarajevo",
      "Sofia", "Strasbourg", "Swansea", "Szeged", "Toulouse",
      "Valona", "Varna", "Venice", "Vienna", "Zagreb", "Zurich",
      "North Sea", "English Channel", "Irish Sea",
      "Atlantic Ocean", "Bay of Biscay", "Mediterranean Sea",
      "Tyrrhenian Sea", "Ionian Sea", "Adriatic Sea",
      "Black Sea", "Unknown City", "Unknown Sea", "Hiding",
      "Double Back 1", "Double Back 2", "Double Back 3",
      "Double Back 4", "Double Back 5",
      "Teleport to Castle Dracula"};
      
   return placeNames[l];
}

static char *getPlayerName(playerCode p) {
   assert(p < NUM_PLAYERS && p >= 0);
   
   char *playerNames[] = {"Lord Godalming", "Dr. Seward", "Van Helsing",
      "Mina Harker", "Dracula"};
   
   return playerNames[p];
}
#ifdef DEBUG
static void dumpMoves(HunterView hv) {
   char *moves[] = {"None", "Trap", "Dracula", "Vampire"};
   int i, j;
   for (i = 0; i < hv->movesPlayed;i++) {
      moveData *currentMove = &(hv->moves[i]);
      printf("Move Number: %d\n", currentMove->moveNumber);
      printf("Player Turn: %s\n", getPlayerName(currentMove->player));
      printf("Location code: %s\n", getLocationName(currentMove->location));
      
      if (currentMove->player == PLAYER_DRACULA) {
         printf("Dracula Move:\n");
         printf("\tPlaced Trap: %s\n", truthToString(currentMove->draculaMove.placedTrap));         
         printf("\tVampire Placed: %s\n", truthToString(currentMove->draculaMove.vampirePlaced));
         printf("\tVampire Matured: %s\n", truthToString(currentMove->draculaMove.vampireMatured));
         printf("\tTrap Left Trail: %s\n", truthToString(currentMove->draculaMove.trapLeftTrail));
      } else {
         for (j = 0; (j < 4) && (currentMove->hunterEncounter[j].encounterType != ENCOUNTER_NONE); j++) {
            printf("Hunter Encounter Number %d:\n", j);
            assert(currentMove->hunterEncounter[j].encounterType < NUM_ENCOUNTERS && currentMove->hunterEncounter[j].encounterType >= 0);
            printf("\tEncounter Type: %s\n", moves[currentMove->hunterEncounter[j].encounterType]);
         }
      }
      
      printf ("\n");
   }
}
#endif
static playerCode charToPlayerCode(char player) {
   playerCode result;
   if (player == 'G') {
      result = PLAYER_LORD_GODALMING;
   } else if (player == 'S') {
      result = PLAYER_DR_SEWARD;
   } else if (player == 'H') {
      result = PLAYER_VAN_HELSING;
   } else if (player == 'M') {
      result = PLAYER_MINA_HARKER;
   } else if (player == 'D') {
      result = PLAYER_DRACULA;
   } else {
      assert(FALSE);
   }
   return result;
}

static locationCode strToLocationCode(char *location) {
   char *cityCodes[] = {"AL", "AM", "AT", "BA", "BI", "BE", "BR", "BO", "BU", "BC",
                   "BD", "CA", "CG", "CD", "CF", "CO", "CN", "DU", "ED", "FL",
                   "FR", "GA", "GW", "GE", "GO", "GR", "HA", "JM", "KL", "LE",
                   "LI", "LS", "LV", "LO", "MA", "MN", "MR", "MI", "MU", "NA",
                   "NP", "NU", "PA", "PL", "PR", "RO", "SA", "SN", "SR", "SJ",
                   "SO", "ST", "SW", "SZ", "TO", "VA", "VR", "VE", "VI", "ZA",
                   "ZU", "NS", "EC", "IS", "AO", "BB", "MS", "TS", "IO", "AS",
                   "BS", "C?", "S?", "HI", "D1", "D2", "D3", "D4", "D5", "TP"};
   int i, foundCode = FALSE, code;
   
   assert(strlen(location) == 2);
   
   for (i = 0; i < NUM_LOCATIONS && !foundCode; i++) {
      if (strncmp(cityCodes[i], location, 3) == 0) {
         code = i;
         foundCode = TRUE;
      }
   }
   
   assert(foundCode);
   return code;
}


// Gets the past locations of Dracula - turnNumber will contain the round number from
// when dracula was last seen.
locationCode HunterView_LastDraculaLocation(HunterView hv, int *roundNumber) {

   moveData move;
   int i, location, foundLastLocation = FALSE;
   
   for (i = hv->movesPlayed; !foundLastLocation && i != 0 ; i--) {
      move = hv->moves[i];
      if (move.player == PLAYER_DRACULA && isRealLocation(move.location) ) {
         location = move.location;
         *roundNumber = move.moveNumber/5;
         foundLastLocation = TRUE;
      }
   } 
   
   if (!foundLastLocation) {
       location = -1;
       *roundNumber = -1;
   }
   
   return location;
}

// Returns an array with the location codes for the last 6 Dracula Moves
// Should we be giving more data instead? IE asking if things were placed or not, etc?
int HunterView_DraculaTrail(HunterView hv, locationCode* trail) {
   
   moveData move;
   int trailCount = 0, currentMove = hv->movesPlayed;
   
   while (trailCount < TRAIL_LENGTH && currentMove >= 0) {
      move = hv->moves[currentMove];
      if (move.player == PLAYER_DRACULA) {
         trail[trailCount] = move.location;
         trailCount++;
      }
      
      currentMove--;
   }
   return trailCount;
}

// returns an array of strings, each string being MESSAGE_SIZE (100) chars long, with a NULL byte somewhere in it
// each message links up to the play at that index in game history
char **HunterView_HunterMessages(HunterView this) {
   return this->playerMessages;
}


void exploreTrainStops (Graph map, locationCode station, int remainingMoves, char legalLocations[NUM_MAP_LOCATIONS]) {\
   printf("Exploring Train stops with remaining depth: %d from station: %s\n", remainingMoves, getLocationName(station));
   // this station is a legal location
   legalLocations[station] = TRUE;
   // if there are more train moves, we also branch out and find any other options
   if (remainingMoves > 0) {
      remainingMoves--;
      char nextStations[NUM_MAP_LOCATIONS] = {0};
      allTrainMoves(map, station, nextStations);
      
      locationCode station = 0;
      while (station < NUM_MAP_LOCATIONS) {
         if (nextStations[station] == TRUE) {
            exploreTrainStops(map, station, remainingMoves, legalLocations);
         }
         station++;
      }
   }
}

locationCode *allLegalMoves(locationCode playerLocation, int roundNumber, hunterCode hc, int *length) {
   assert(hc < NUM_PLAYERS && hc >= 0);
   
   
   int trainMoves = (hc + roundNumber) % 4;
   char legalLocations[NUM_MAP_LOCATIONS] = {0};
   
   Graph map = createGraph();
   
   allRoadMoves(map, playerLocation, legalLocations);
   allSeaMoves(map, playerLocation, legalLocations);
   
   if (hc != PLAYER_DRACULA) {
      exploreTrainStops(map, playerLocation, trainMoves, legalLocations);
   } else {
      legalLocations[ST_JOSEPH_AND_ST_MARYS] = FALSE;
   }
   
   // convert array of booleans in to just a normal array!
   locationCode *results = malloc(NUM_MAP_LOCATIONS);
   int legalLocationsIndex = 0, resultIndex = 0;
   while (legalLocationsIndex < NUM_MAP_LOCATIONS) {
      if (legalLocations[legalLocationsIndex] == TRUE) {
         results[resultIndex] = legalLocationsIndex;
         resultIndex++;
      }
      
      legalLocationsIndex++;
   }
   
   *length = resultIndex;
   return results;
}


hunterCode HunterView_CurrentHunter(HunterView hv) {
   assert(hv != NULL);
   hunterCode currentPlayer = (hv->movesPlayed) % NUM_PLAYERS;
   return currentPlayer;
}

int HunterView_CurrentRound(HunterView hv) {
   return hv->movesPlayed/5;
}

int HunterView_GameScore(HunterView hv) {
   return hv->gameScore;
}

int HunterView_HunterHealth(HunterView hv, hunterCode hunterID) {
   return hv->players[hunterID].health;
}

locationCode HunterView_HunterLocation(HunterView hv, hunterCode hunterID) {
   return hv->players[hunterID].location;
}

int HunterView_DraculaHealth(HunterView hv) {
   return hv->players[PLAYER_DRACULA].health;
}
