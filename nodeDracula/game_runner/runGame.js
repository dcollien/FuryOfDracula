var fs = require( 'fs' );
var path = require( 'path' );

var spawn = require( 'child_process' ).spawn;

var list = require( './jsFun/listLike' );
var assert = require( './jsFun/assert' );


var gameRunner = require( './gameRunner' );

var gameRules = require( './draculaRules/gameRules' );

var game = new gameRunner( );


function runPlayer( playerProgram, programInput, callback, args ) {
   console.log(playerProgram + args);
   console.log(JSON.stringify(programInput));
   var killed = false;
	
	var stdout = '';
	var stderr = '';
	
	// store stdout
	var writeOut = function( data ) {
		if ( !!data ) {
			stdout += data;
		}
	};
	
	// store stderr
	var writeErr = function( data ) {
		if ( !!data ) {
			stderr += data;
		}
	}
	assert( playerProgram, 'playerProgram undefined. in runPlayer' );
	var playerProcess = spawn( playerProgram, args );
	
	playerProcess.on( 'exit', function( code, signal ) {

      if (code != 0) {
         console.log("Program exited with exit code " + code);
      }

      var outputObject;
		// expect JSON output on stdout, normal output on stderr
      console.log("STDOUT: " + stdout + "");
      console.log("STDERR: " + stderr + "");	

      try {
			outputObject = JSON.parse(stdout);
		} catch( e ) {
   		console.log("Not valid JSON: \""+ stdout + "\"");
         console.log(e);
         outputObject = { };
		}
		
		callback( outputObject, stderr );
	} );
   
   playerProcess.on( 'SIGSEGV', function () {
      console.log('SEG FAULT!!! FAIL! Silly undergrads...');
   });

	playerProcess.stdout.on( 'data', writeOut );
	playerProcess.stderr.on( 'data', writeErr );
	
	// sent programInput object to subprocess as stdin
	playerProcess.stdin.write( JSON.stringify( programInput ) );
	playerProcess.stdin.end( );
}

function runGame( playerPrograms ) {
	game.setRules( gameRules );
	
	game.on( 'playerTurn', function( playerIndex, playerInput ) {
		//console.log( "> " );
		//console.log( "> ----------------------------------------- <" );
		//console.log( "> Input for player " + playerIndex + ":" );
		
		//console.log( "> +++" );
		//list.each( playerInput, function( value, key ) {
		//	if ( key === "messages" ) return; // DEBUG
		//	console.log( "  " + key + ": " );
		//	console.log( value );
		//} );
		//console.log( "> ---" );
		
		var programToRun = playerPrograms[playerIndex];
		var args = [];
	   //console.log(playerPrograms[playerIndex]);
		if (programToRun.indexOf(' ') != -1) {
			args = programToRun.split(' ');
			programToRun = args.shift();
      }
		if ( !programToRun ) {
			game.playMove( );
		} else {
			console.log( "> Running player " + playerIndex + "... " );
			runPlayer( programToRun, playerInput, function( playerMove, playerOutput ) {
				// spit out the player's output
		      //		console.log( "# ---   Player Output   ---" );
	         //		console.log( playerOutput );
	         //		console.log( "# --- End Player Output ---" );
				
				// play the player's move
				game.playMove( playerMove );
			}, args );
		}
	} );
	
	game.on( 'playerDisqualified', function( playerIndex, move ) {
		console.log( "> Player " + playerIndex + " disqualified for illegal move." );
		console.log( "> +++ " );
		list.each( move, function( value, key ) {
			console.log( "  " + key + ": " + value );
		} );
		console.log( "> --- " );
	} );
	
	game.on( 'turnFinished', function( moveMade, playerIndex ) {
		console.log( "> Player " + playerIndex + " made move:" );
		
		console.log( "> +++" );
		list.each( moveMade, function( value, key ) {
			console.log( "  " + key + ": " + value );
		} );
		console.log( "> ---" );
		
	} );
	
	game.on( 'gameOver', function( ) {
		console.log( "> End of game: " );
		console.log( "> +++" );
		list.each( game.getOutput( ), function( value, key ) {
			console.log( "  " + key + ": " + value );
		} );
		console.log( "> ---" );

		console.log( "> Game Over" );
      console.log(game.score);
      console.log(game.round);
      for (i in this.isDisqualified) {
          console.log("Player " + i + " was disqualified? " + this.isDisqualified[i]);
      }

} );
	
	game.run( );
}

// ignore first two arguments ("node" and script name)
runGame( process.argv.slice( 2 ) );











