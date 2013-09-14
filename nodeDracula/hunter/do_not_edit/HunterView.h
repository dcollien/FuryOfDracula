// HunterView.h
// Interface for HunterViewADT
// Tutorial Group:
// Tutor:
// Date:
// Version:

typedef struct hunterView *HunterView;


// newHunterView creates a new hunter view to summarise the current state of 
// the game.
//
// pastPlays is a string of all the plays made in the game so far by all
// players (including Dracula) from earliest to most recent.
//
//
// messages is an array containing a playerMessage for each play in the game
// so far. It will have exactly the same number of elements as there are plays
// in pastPlays.  The message from the first play will be at index 0, and so on.
// The contents of each playerMessage will be exactly as provided by the player.
//
// The "playerMessage" type is defined in game.h.
// You are free to ignore messages if you wish.

HunterView newHunterView (char *pastPlays, playerMessage messages[]);


// this function frees all memory previously allocated for the HunterView 
// toBeDeleted.  toBeDeleted should not be accessed after the call.
void disposeHunterView (HunterView toBeDeleted);