var gameState = require( './gameState' );
var gameLogic = require( './gameLogic' );
var gameMoves = require( './gameMoves' );
var gameMap   = require( './gameMap' );

var gameSerialiser = require( './gameSerialiser' );


var assert = require( '../jsFun/assert' );

var rules = {
   state: gameState,

   numPlayers: 5,

   getGameOutput: function( state ) {
	  return {
		 score: state.score,
		 revealedPastPlays: gameSerialiser.generatePastPlays( state, "dracula" ),
		 messages: JSON.stringify( state.messages )
	  };
   },

   getPlayerInput: function( state ) {
	  return {
		 pastPlays: gameSerialiser.generatePastPlays( state ),
		 messages: state.messages
	  }
   },

   isGameOver: function( state ) {
	  return state.isOver;
   },

   playDefaultMove: function( state ) {
	  var move;

	  var randomMessages = [
		 "+++Mr. Jelly! Mr. Jelly!+++",
		 "+++Error At Address: 14, Treacle Mine Road, Ankh-Morpork+++",
		 "+++MELON MELON MELON+++",
		 "+++Divide By Cucumber Error. Please Reinstall Universe And Reboot+++",
		 "+++Whoops! Here Comes The Cheese!+++",
		 "+++Oneoneoneoneoneoneone+++",
		 "+++Out Of Cheese Error+++"
	  ];

	  var randomIndex = Math.floor( Math.random( ) * randomMessages.length );
	  var message = randomMessages[randomIndex];
	  state.messages.push( message );

	  if ( state.currentPlayer.type === 'hunter' ) {
                 console.log("generating default hunter move");
		 if ( state.round === 0 ) {
			move = gameMap.hospitalCityCode;
		 } else {
			move = state.currentPlayer.location;
		 }

		 console.log( "> Moving from: " + state.currentPlayer.location );
		 console.log( "> Life Points: " + state.currentPlayer.lifePoints );

		 gameLogic.doHunterMove( state, move );


	  } else {
 		 console.log("generating default dracula move");
		 var legalDraculaMoves = gameMoves.getValidDraculaMoves( state );

		 if ( legalDraculaMoves.length === 0 ) {
			move = constants.teleportCode;
		 } else {
			var randomIndex = Math.floor( Math.random( ) * legalDraculaMoves.length );
			move = legalDraculaMoves[randomIndex];
		 }



		 console.log( "> Dracula move: " );
		 console.log( "> +++" );
		 console.log( "  move: " + move );
		 console.log( "  message: " + message );
		 console.log( "> ---" );

		 console.log( "> Moving from: " + state.currentPlayer.location );
		 console.log( "> Blood Points: " + state.currentPlayer.bloodPoints );


		 gameLogic.doDraculaMove( state, move );
	  }
   },

   isLegalMove: function( state, playerResult ) {
	  var move = playerResult.move;

	  if ( state.currentPlayer.type === 'hunter' ) {
		 return gameMoves.isLegalHunterMove( state, move );
	  } else {
		 if ( !gameMoves.canDraculaMove( state ) ) {
			return true; // any move is legal if dracula can't move
		 } else {
			return gameMoves.isLegalDraculaMove( state, move );
		 }
	  }
   },

   playMove: function( state, playerResult ) {
	  var move, message;

	  move = playerResult.move;
	  message = playerResult.message;

	  if ( !message ) {
		 message = "";
	  }

	  // add the message to the state
	  state.messages.push( message );


	  console.log( "> Moving from: " + state.currentPlayer.location );

	  if ( state.currentPlayer.type === "hunter" ) {
		 console.log( "> Life Points: " + state.currentPlayer.lifePoints );
	  } else {
		 console.log( "> Blood Points: " + state.currentPlayer.bloodPoints );
	  }

	  if ( state.currentPlayer.type == "hunter" ) {
		 assert( gameMoves.isLegalHunterMove( state, move ) );
		 gameLogic.doHunterMove( state, move );
	  } else if ( state.currentPlayer.type == "dracula" ) {
		 if ( gameMoves.canDraculaMove( state ) ) {
			assert( gameMoves.isLegalDraculaMove( state, move ) );
		 }
		 gameLogic.doDraculaMove( state, move );
	  }
   },

   endTurn: function( state ) {
	  if ( state.dracula.bloodPoints <= 0 ) {
		 // When Dracula has no blood points left the game is over
		 state.isOver = true;
	  } else if ( state.score <= 0 ) {
		 // if [the score] ever reaches 0 we say Dracula has utterly won,
		 // the world is doomed, and the game stops at once. We all look
		 // accusingly at the Hunters...
		 state.isOver = true;
	  }

	  // next player
	  state.currentPlayerNumber = (state.currentPlayerNumber + 1) % rules.numPlayers;
	  state.currentPlayer = state.playSequence[state.currentPlayerNumber];
   },

   endRound: function( state ) {
	  console.log( '> End of Round: ', state.round );

	  state.round++;

	  // do research
	  if ( state.hunterRests === 4 ) {
		 gameLogic.doResearch( state );
	  }

	  state.hunterRests = 0;


	  console.log( '> Starting Round: ', state.round );
   }
};

module.exports = rules;
