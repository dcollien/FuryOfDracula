#include "cities.h"

#define GAME_START_SCORE		366
#define SCORE_LOSS_DRACULA_TURN		1
#define SCORE_LOSS_HUNTER_HOSPITAL	6
#define SCORE_LOSS_VAMPIRE_MATURES	13

// Dracula
#define GAME_START_BLOOD_POINTS		40
#define LIFE_LOSS_HUNTER_ENCOUNTER	10
#define LIFE_LOSS_SEA			2
#define LIFE_GAIN_CASTLE_DRACULA	10

// Players
#define PLAYER_LORD_GODALMING	0
#define PLAYER_DR_SEWARD	1
#define PLAYER_VAN_HELSING	2
#define PLAYER_MINA_HARKER	3
#define PLAYER_DRACULA		4

#define NUM_PLAYERS	5

#define GAME_START_HUNTER_LIFE_POINTS	9
#define LIFE_LOSS_TRAP_ENCOUNTER	2
#define LIFE_LOSS_DRACULA_ENCOUNTER	4
#define LIFE_GAIN_REST			3
#define MAX_HUNTER_LIFE_POINTS		GAME_START_HUNTER_LIFE_POINTS
#define TRAIL_LENGTH 6

#define MAX_ROUNDS_IN_GAME	(GAME_START_SCORE/SCORE_LOSS_DRACULA_TURN)
#define MAX_MOVES_IN_GAME	(MAX_ROUNDS_IN_GAME * NUM_PLAYERS)

typedef struct hunterView *HunterView;

// Structs
#include "Graph.h"

typedef int hunterCode;
typedef int playerCode;

// Constructor
HunterView newHunterView(char *pastPlays, playerMessage messages[]);

// Destructor
void disposeHunterView (HunterView toBeDeleted);

// HunterView_CurrentHunter looks up the identity of this hunter, and returns a
// hunterCode representing it.
hunterCode HunterView_CurrentHunter(HunterView this);

// HunterView_CurrentRound looks up the identity of this hunter, and returns an int
// representing it.
int HunterView_CurrentRound(HunterView this);

// Returns game score.
int HunterView_GameScore(HunterView this);

// Get information about a hunter by their ID - things like health
int HunterView_HunterHealth(HunterView this, hunterCode hunterID);

locationCode HunterView_HunterLocation(HunterView this, hunterCode hunterID);

// Gets the past locations of Dracula - turnNumber gets the turn number from
// when dracula was last seen.
locationCode HunterView_LastDraculaLocation(HunterView this, int *roundNumber);

// Dracula's trail. Expects a buffer of size 6, returns the length of Dracula's trail
int HunterView_DraculaTrail(HunterView this, locationCode *trail);

// Gets the current health of dracula
int HunterView_DraculaHealth(HunterView this);

// returns an array of locationCodes for every possible move for a given hunter. Length of array is returned in the length paramater
locationCode *allLegalMoves(locationCode playerLocation, int turnNumber, hunterCode hc, int *length);


// returns an array of messages
char **HunterView_HunterMessages(HunterView this);