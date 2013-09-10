#include "cities.h"

typedef struct graph *Graph;

#define ROAD 1
#define TRAIN 2
#define SEA 3

typedef int locationCode;
typedef int transportCode;

Graph createGraph (void);

void allRoadMoves (Graph g, locationCode l, char locations[NUM_MAP_LOCATIONS]);
void allSeaMoves (Graph g, locationCode l, char locations[NUM_MAP_LOCATIONS]);
void allTrainMoves (Graph g, locationCode l, char locations[NUM_MAP_LOCATIONS]);