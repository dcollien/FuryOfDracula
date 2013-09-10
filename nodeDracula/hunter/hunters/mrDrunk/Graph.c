#include "Graph.h"

#include <stdlib.h>
#include <assert.h>

#define TRUE  1
#define FALSE 0
typedef struct edge *Edge;
typedef struct vertex *Vertex;

typedef struct vertex {
   locationCode location;
   Edge next;
} vertex;

typedef struct edge {
   locationCode location;
   transportCode type;
   Edge next;
} edge;

typedef struct graph {
   vertex cities[NUM_MAP_LOCATIONS];
} graph;

void joinCities(Graph g);

Graph createGraph (void) {
   Graph newGraph = malloc(sizeof(graph));
   int mapLocation = 0;
   while (mapLocation < NUM_MAP_LOCATIONS) {
      newGraph->cities[mapLocation].location = mapLocation;
      newGraph->cities[mapLocation].next = NULL;
      mapLocation++; 
   }
    
   joinCities(newGraph);
   return newGraph;
}

void addDirectionalLink(Graph g, locationCode start, locationCode end, transportCode type) {
   Edge newEdge;
   newEdge = malloc(sizeof(edge));
   newEdge->type = type;
   newEdge->location = end;

   newEdge->next = g->cities[start].next;
   g->cities[start].next = newEdge;
}

void addLink(Graph g, locationCode start, locationCode end, transportCode type) {
   addDirectionalLink(g, start, end, type);
   addDirectionalLink(g, end, start, type);
}

// fills in an array of locations with boolean TRUE values if this move is available from a given location on a given graph
void allMovesOfType (Graph g, locationCode l, transportCode type, char locations[NUM_MAP_LOCATIONS]) {
   assert(g != NULL);
   assert(l < NUM_MAP_LOCATIONS && l >= 0);
   assert(type == ROAD || type == SEA || type == TRAIN);

   Edge current = g-> cities[l].next;
   while (current != NULL) {
      if (current->type == type) {
         locations[current->location] = TRUE;
      }
      current = current->next;
   }
}

void allRoadMoves (Graph g, locationCode l, char locations[NUM_MAP_LOCATIONS]) {
   allMovesOfType(g, l, ROAD, locations);
}

void allSeaMoves (Graph g, locationCode l, char locations[NUM_MAP_LOCATIONS]) {
   allMovesOfType(g, l, SEA, locations);
}

void allTrainMoves (Graph g, locationCode l, char locations[NUM_MAP_LOCATIONS]) {
   allMovesOfType(g, l, TRAIN, locations);
}

void joinCities (Graph g) {
   addLink(g, ALICANTE, GRANADA, ROAD);
   addLink(g, ALICANTE, MADRID, ROAD);
   addLink(g, ALICANTE, SARAGOSSA, ROAD);
   addLink(g, AMSTERDAM, BRUSSELS, ROAD);
   addLink(g, AMSTERDAM, COLOGNE, ROAD);
   addLink(g, ATHENS, VALONA, ROAD);
   addLink(g, BARCELONA, SARAGOSSA, ROAD);
   addLink(g, BARCELONA, TOULOUSE, ROAD);
   addLink(g, BARI, NAPLES, ROAD);
   addLink(g, BARI, ROME, ROAD);
   addLink(g, BELGRADE, BUCHAREST, ROAD);
   addLink(g, BELGRADE, KLAUSENBURG, ROAD);
   addLink(g, BELGRADE, SARAJEVO, ROAD);
   addLink(g, BELGRADE, SOFIA, ROAD);
   addLink(g, BELGRADE, ST_JOSEPH_AND_ST_MARYS, ROAD);
   addLink(g, BELGRADE, SZEGED, ROAD);
   addLink(g, BERLIN, HAMBURG, ROAD);
   addLink(g, BERLIN, LEIPZIG, ROAD);
   addLink(g, BERLIN, PRAGUE, ROAD);
   addLink(g, BORDEAUX, CLERMONT_FERRAND, ROAD);
   addLink(g, BORDEAUX, NANTES, ROAD);
   addLink(g, BORDEAUX, SARAGOSSA, ROAD);
   addLink(g, BORDEAUX, TOULOUSE, ROAD);
   addLink(g, BRUSSELS, AMSTERDAM, ROAD);
   addLink(g, BRUSSELS, COLOGNE, ROAD);
   addLink(g, BRUSSELS, LE_HAVRE, ROAD);
   addLink(g, BRUSSELS, PARIS, ROAD);
   addLink(g, BRUSSELS, STRASBOURG, ROAD);
   addLink(g, BUCHAREST, BELGRADE, ROAD);
   addLink(g, BUCHAREST, CONSTANTA, ROAD);
   addLink(g, BUCHAREST, GALATZ, ROAD);
   addLink(g, BUCHAREST, KLAUSENBURG, ROAD);
   addLink(g, BUCHAREST, SOFIA, ROAD);
   addLink(g, BUDAPEST, KLAUSENBURG, ROAD);
   addLink(g, BUDAPEST, SZEGED, ROAD);
   addLink(g, BUDAPEST, VIENNA, ROAD);
   addLink(g, BUDAPEST, ZAGREB, ROAD);
   addLink(g, CADIZ, GRANADA, ROAD);
   addLink(g, CADIZ, LISBON, ROAD);
   addLink(g, CADIZ, MADRID, ROAD);
   addLink(g, CASTLE_DRACULA, GALATZ, ROAD);
   addLink(g, CASTLE_DRACULA, KLAUSENBURG, ROAD);
   addLink(g, CLERMONT_FERRAND, BORDEAUX, ROAD);
   addLink(g, CLERMONT_FERRAND, GENEVA, ROAD);
   addLink(g, CLERMONT_FERRAND, MARSEILLES, ROAD);
   addLink(g, CLERMONT_FERRAND, NANTES, ROAD);
   addLink(g, CLERMONT_FERRAND, PARIS, ROAD);
   addLink(g, CLERMONT_FERRAND, TOULOUSE, ROAD);
   addLink(g, COLOGNE, AMSTERDAM, ROAD);
   addLink(g, COLOGNE, BRUSSELS, ROAD);
   addLink(g, COLOGNE, FRANKFURT, ROAD);
   addLink(g, COLOGNE, HAMBURG, ROAD);
   addLink(g, COLOGNE, LEIPZIG, ROAD);
   addLink(g, COLOGNE, STRASBOURG, ROAD);
   addLink(g, CONSTANTA, BUCHAREST, ROAD);
   addLink(g, CONSTANTA, GALATZ, ROAD);
   addLink(g, CONSTANTA, VARNA, ROAD);
   addLink(g, DUBLIN, GALWAY, ROAD);
   addLink(g, EDINBURGH, MANCHESTER, ROAD);
   addLink(g, FLORENCE, GENOA, ROAD);
   addLink(g, FLORENCE, ROME, ROAD);
   addLink(g, FLORENCE, VENICE, ROAD);
   addLink(g, FRANKFURT, COLOGNE, ROAD);
   addLink(g, FRANKFURT, LEIPZIG, ROAD);
   addLink(g, FRANKFURT, NUREMBURG, ROAD);
   addLink(g, FRANKFURT, STRASBOURG, ROAD);
   addLink(g, GALATZ, BUCHAREST, ROAD);
   addLink(g, GALATZ, CASTLE_DRACULA, ROAD);
   addLink(g, GALATZ, CONSTANTA, ROAD);
   addLink(g, GALATZ, KLAUSENBURG, ROAD);
   addLink(g, GALWAY, DUBLIN, ROAD);
   addLink(g, GENEVA, CLERMONT_FERRAND, ROAD);
   addLink(g, GENEVA, MARSEILLES, ROAD);
   addLink(g, GENEVA, PARIS, ROAD);
   addLink(g, GENEVA, STRASBOURG, ROAD);
   addLink(g, GENEVA, ZURICH, ROAD);
   addLink(g, GENOA, FLORENCE, ROAD);
   addLink(g, GENOA, MARSEILLES, ROAD);
   addLink(g, GENOA, MILAN, ROAD);
   addLink(g, GENOA, VENICE, ROAD);
   addLink(g, GRANADA, ALICANTE, ROAD);
   addLink(g, GRANADA, CADIZ, ROAD);
   addLink(g, GRANADA, MADRID, ROAD);
   addLink(g, HAMBURG, BERLIN, ROAD);
   addLink(g, HAMBURG, COLOGNE, ROAD);
   addLink(g, HAMBURG, LEIPZIG, ROAD);
   addLink(g, KLAUSENBURG, BELGRADE, ROAD);
   addLink(g, KLAUSENBURG, BUCHAREST, ROAD);
   addLink(g, KLAUSENBURG, BUDAPEST, ROAD);
   addLink(g, KLAUSENBURG, CASTLE_DRACULA, ROAD);
   addLink(g, KLAUSENBURG, GALATZ, ROAD);
   addLink(g, KLAUSENBURG, SZEGED, ROAD);
   addLink(g, LEIPZIG, BERLIN, ROAD);
   addLink(g, LEIPZIG, COLOGNE, ROAD);
   addLink(g, LEIPZIG, FRANKFURT, ROAD);
   addLink(g, LEIPZIG, HAMBURG, ROAD);
   addLink(g, LEIPZIG, NUREMBURG, ROAD);
   addLink(g, LE_HAVRE, BRUSSELS, ROAD);
   addLink(g, LE_HAVRE, NANTES, ROAD);
   addLink(g, LE_HAVRE, PARIS, ROAD);
   addLink(g, LISBON, CADIZ, ROAD);
   addLink(g, LISBON, MADRID, ROAD);
   addLink(g, LISBON, SANTANDER, ROAD);
   addLink(g, LIVERPOOL, MANCHESTER, ROAD);
   addLink(g, LIVERPOOL, SWANSEA, ROAD);
   addLink(g, LONDON, MANCHESTER, ROAD);
   addLink(g, LONDON, PLYMOUTH, ROAD);
   addLink(g, LONDON, SWANSEA, ROAD);
   addLink(g, MADRID, ALICANTE, ROAD);
   addLink(g, MADRID, CADIZ, ROAD);
   addLink(g, MADRID, GRANADA, ROAD);
   addLink(g, MADRID, LISBON, ROAD);
   addLink(g, MADRID, SANTANDER, ROAD);
   addLink(g, MADRID, SARAGOSSA, ROAD);
   addLink(g, MANCHESTER, EDINBURGH, ROAD);
   addLink(g, MANCHESTER, LIVERPOOL, ROAD);
   addLink(g, MANCHESTER, LONDON, ROAD);
   addLink(g, MARSEILLES, CLERMONT_FERRAND, ROAD);
   addLink(g, MARSEILLES, GENEVA, ROAD);
   addLink(g, MARSEILLES, GENOA, ROAD);
   addLink(g, MARSEILLES, MILAN, ROAD);
   addLink(g, MARSEILLES, TOULOUSE, ROAD);
   addLink(g, MARSEILLES, ZURICH, ROAD);
   addLink(g, MILAN, GENOA, ROAD);
   addLink(g, MILAN, MARSEILLES, ROAD);
   addLink(g, MILAN, MUNICH, ROAD);
   addLink(g, MILAN, VENICE, ROAD);
   addLink(g, MILAN, ZURICH, ROAD);
   addLink(g, MUNICH, MILAN, ROAD);
   addLink(g, MUNICH, NUREMBURG, ROAD);
   addLink(g, MUNICH, STRASBOURG, ROAD);
   addLink(g, MUNICH, VENICE, ROAD);
   addLink(g, MUNICH, VIENNA, ROAD);
   addLink(g, MUNICH, ZAGREB, ROAD);
   addLink(g, MUNICH, ZURICH, ROAD);
   addLink(g, NANTES, BORDEAUX, ROAD);
   addLink(g, NANTES, CLERMONT_FERRAND, ROAD);
   addLink(g, NANTES, LE_HAVRE, ROAD);
   addLink(g, NANTES, PARIS, ROAD);
   addLink(g, NAPLES, BARI, ROAD);
   addLink(g, NAPLES, ROME, ROAD);
   addLink(g, NUREMBURG, FRANKFURT, ROAD);
   addLink(g, NUREMBURG, LEIPZIG, ROAD);
   addLink(g, NUREMBURG, MUNICH, ROAD);
   addLink(g, NUREMBURG, PRAGUE, ROAD);
   addLink(g, NUREMBURG, STRASBOURG, ROAD);
   addLink(g, PARIS, BRUSSELS, ROAD);
   addLink(g, PARIS, CLERMONT_FERRAND, ROAD);
   addLink(g, PARIS, GENEVA, ROAD);
   addLink(g, PARIS, LE_HAVRE, ROAD);
   addLink(g, PARIS, NANTES, ROAD);
   addLink(g, PARIS, STRASBOURG, ROAD);
   addLink(g, PLYMOUTH, LONDON, ROAD);
   addLink(g, PRAGUE, BERLIN, ROAD);
   addLink(g, PRAGUE, NUREMBURG, ROAD);
   addLink(g, PRAGUE, VIENNA, ROAD);
   addLink(g, ROME, BARI, ROAD);
   addLink(g, ROME, FLORENCE, ROAD);
   addLink(g, ROME, NAPLES, ROAD);
   addLink(g, SALONICA, SOFIA, ROAD);
   addLink(g, SALONICA, VALONA, ROAD);
   addLink(g, SANTANDER, LISBON, ROAD);
   addLink(g, SANTANDER, MADRID, ROAD);
   addLink(g, SANTANDER, SARAGOSSA, ROAD);
   addLink(g, SARAGOSSA, ALICANTE, ROAD);
   addLink(g, SARAGOSSA, BARCELONA, ROAD);
   addLink(g, SARAGOSSA, BORDEAUX, ROAD);
   addLink(g, SARAGOSSA, MADRID, ROAD);
   addLink(g, SARAGOSSA, SANTANDER, ROAD);
   addLink(g, SARAGOSSA, TOULOUSE, ROAD);
   addLink(g, SARAJEVO, BELGRADE, ROAD);
   addLink(g, SARAJEVO, SOFIA, ROAD);
   addLink(g, SARAJEVO, ST_JOSEPH_AND_ST_MARYS, ROAD);
   addLink(g, SARAJEVO, VALONA, ROAD);
   addLink(g, SARAJEVO, ZAGREB, ROAD);
   addLink(g, SOFIA, BELGRADE, ROAD);
   addLink(g, SOFIA, BUCHAREST, ROAD);
   addLink(g, SOFIA, SALONICA, ROAD);
   addLink(g, SOFIA, SARAJEVO, ROAD);
   addLink(g, SOFIA, VALONA, ROAD);
   addLink(g, SOFIA, VARNA, ROAD);
   addLink(g, STRASBOURG, BRUSSELS, ROAD);
   addLink(g, STRASBOURG, COLOGNE, ROAD);
   addLink(g, STRASBOURG, FRANKFURT, ROAD);
   addLink(g, STRASBOURG, GENEVA, ROAD);
   addLink(g, STRASBOURG, MUNICH, ROAD);
   addLink(g, STRASBOURG, NUREMBURG, ROAD);
   addLink(g, STRASBOURG, PARIS, ROAD);
   addLink(g, STRASBOURG, ZURICH, ROAD);
   addLink(g, ST_JOSEPH_AND_ST_MARYS, BELGRADE, ROAD);
   addLink(g, ST_JOSEPH_AND_ST_MARYS, SARAJEVO, ROAD);
   addLink(g, ST_JOSEPH_AND_ST_MARYS, SZEGED, ROAD);
   addLink(g, ST_JOSEPH_AND_ST_MARYS, ZAGREB, ROAD);
   addLink(g, SWANSEA, LIVERPOOL, ROAD);
   addLink(g, SWANSEA, LONDON, ROAD);
   addLink(g, SZEGED, BELGRADE, ROAD);
   addLink(g, SZEGED, BUDAPEST, ROAD);
   addLink(g, SZEGED, KLAUSENBURG, ROAD);
   addLink(g, SZEGED, ST_JOSEPH_AND_ST_MARYS, ROAD);
   addLink(g, SZEGED, ZAGREB, ROAD);
   addLink(g, TOULOUSE, BARCELONA, ROAD);
   addLink(g, TOULOUSE, BORDEAUX, ROAD);
   addLink(g, TOULOUSE, CLERMONT_FERRAND, ROAD);
   addLink(g, TOULOUSE, MARSEILLES, ROAD);
   addLink(g, TOULOUSE, SARAGOSSA, ROAD);
   addLink(g, VALONA, ATHENS, ROAD);
   addLink(g, VALONA, SALONICA, ROAD);
   addLink(g, VALONA, SARAJEVO, ROAD);
   addLink(g, VALONA, SOFIA, ROAD);
   addLink(g, VARNA, CONSTANTA, ROAD);
   addLink(g, VARNA, SOFIA, ROAD);
   addLink(g, VENICE, FLORENCE, ROAD);
   addLink(g, VENICE, GENOA, ROAD);
   addLink(g, VENICE, MILAN, ROAD);
   addLink(g, VENICE, MUNICH, ROAD);
   addLink(g, VIENNA, BUDAPEST, ROAD);
   addLink(g, VIENNA, MUNICH, ROAD);
   addLink(g, VIENNA, PRAGUE, ROAD);
   addLink(g, VIENNA, ZAGREB, ROAD);
   addLink(g, ZAGREB, BUDAPEST, ROAD);
   addLink(g, ZAGREB, MUNICH, ROAD);
   addLink(g, ZAGREB, SARAJEVO, ROAD);
   addLink(g, ZAGREB, ST_JOSEPH_AND_ST_MARYS, ROAD);
   addLink(g, ZAGREB, SZEGED, ROAD);
   addLink(g, ZAGREB, VIENNA, ROAD);
   addLink(g, ZURICH, GENEVA, ROAD);
   addLink(g, ZURICH, MARSEILLES, ROAD);
   addLink(g, ZURICH, MILAN, ROAD);
   addLink(g, ZURICH, MUNICH, ROAD);
   addLink(g, ZURICH, STRASBOURG, ROAD);

   addLink(g, ALICANTE, BARCELONA, TRAIN);
   addLink(g, ALICANTE, MADRID, TRAIN);
   addLink(g, BARCELONA, ALICANTE, TRAIN);
   addLink(g, BARCELONA, SARAGOSSA, TRAIN);
   addLink(g, BARI, NAPLES, TRAIN);
   addLink(g, BELGRADE, SOFIA, TRAIN);
   addLink(g, BELGRADE, SZEGED, TRAIN);
   addLink(g, BERLIN, HAMBURG, TRAIN);
   addLink(g, BERLIN, LEIPZIG, TRAIN);
   addLink(g, BERLIN, PRAGUE, TRAIN);
   addLink(g, BORDEAUX, PARIS, TRAIN);
   addLink(g, BORDEAUX, SARAGOSSA, TRAIN);
   addLink(g, BRUSSELS, COLOGNE, TRAIN);
   addLink(g, BRUSSELS, PARIS, TRAIN);
   addLink(g, BUCHAREST, CONSTANTA, TRAIN);
   addLink(g, BUCHAREST, GALATZ, TRAIN);
   addLink(g, BUCHAREST, SZEGED, TRAIN);
   addLink(g, BUDAPEST, SZEGED, TRAIN);
   addLink(g, BUDAPEST, VIENNA, TRAIN);
   addLink(g, COLOGNE, BRUSSELS, TRAIN);
   addLink(g, COLOGNE, FRANKFURT, TRAIN);
   addLink(g, CONSTANTA, BUCHAREST, TRAIN);
   addLink(g, EDINBURGH, MANCHESTER, TRAIN);
   addLink(g, FLORENCE, MILAN, TRAIN);
   addLink(g, FLORENCE, ROME, TRAIN);
   addLink(g, FRANKFURT, COLOGNE, TRAIN);
   addLink(g, FRANKFURT, LEIPZIG, TRAIN);
   addLink(g, FRANKFURT, STRASBOURG, TRAIN);
   addLink(g, GALATZ, BUCHAREST, TRAIN);
   addLink(g, GENEVA, MILAN, TRAIN);
   addLink(g, GENOA, MILAN, TRAIN);
   addLink(g, HAMBURG, BERLIN, TRAIN);
   addLink(g, LEIPZIG, BERLIN, TRAIN);
   addLink(g, LEIPZIG, FRANKFURT, TRAIN);
   addLink(g, LEIPZIG, NUREMBURG, TRAIN);
   addLink(g, LE_HAVRE, PARIS, TRAIN);
   addLink(g, LISBON, MADRID, TRAIN);
   addLink(g, LIVERPOOL, MANCHESTER, TRAIN);
   addLink(g, LONDON, MANCHESTER, TRAIN);
   addLink(g, LONDON, SWANSEA, TRAIN);
   addLink(g, MADRID, ALICANTE, TRAIN);
   addLink(g, MADRID, LISBON, TRAIN);
   addLink(g, MADRID, SANTANDER, TRAIN);
   addLink(g, MADRID, SARAGOSSA, TRAIN);
   addLink(g, MANCHESTER, EDINBURGH, TRAIN);
   addLink(g, MANCHESTER, LIVERPOOL, TRAIN);
   addLink(g, MANCHESTER, LONDON, TRAIN);
   addLink(g, MARSEILLES, PARIS, TRAIN);
   addLink(g, MILAN, FLORENCE, TRAIN);
   addLink(g, MILAN, GENEVA, TRAIN);
   addLink(g, MILAN, GENOA, TRAIN);
   addLink(g, MILAN, ZURICH, TRAIN);
   addLink(g, MUNICH, NUREMBURG, TRAIN);
   addLink(g, NAPLES, BARI, TRAIN);
   addLink(g, NAPLES, ROME, TRAIN);
   addLink(g, NUREMBURG, LEIPZIG, TRAIN);
   addLink(g, NUREMBURG, MUNICH, TRAIN);
   addLink(g, PARIS, BORDEAUX, TRAIN);
   addLink(g, PARIS, BRUSSELS, TRAIN);
   addLink(g, PARIS, LE_HAVRE, TRAIN);
   addLink(g, PARIS, MARSEILLES, TRAIN);
   addLink(g, PRAGUE, BERLIN, TRAIN);
   addLink(g, PRAGUE, VIENNA, TRAIN);
   addLink(g, ROME, FLORENCE, TRAIN);
   addLink(g, ROME, NAPLES, TRAIN);
   addLink(g, SALONICA, SOFIA, TRAIN);
   addLink(g, SANTANDER, MADRID, TRAIN);
   addLink(g, SARAGOSSA, BARCELONA, TRAIN);
   addLink(g, SARAGOSSA, BORDEAUX, TRAIN);
   addLink(g, SARAGOSSA, MADRID, TRAIN);
   addLink(g, SOFIA, BELGRADE, TRAIN);
   addLink(g, SOFIA, SALONICA, TRAIN);
   addLink(g, SOFIA, VARNA, TRAIN);
   addLink(g, STRASBOURG, FRANKFURT, TRAIN);
   addLink(g, STRASBOURG, ZURICH, TRAIN);
   addLink(g, SWANSEA, LONDON, TRAIN);
   addLink(g, SZEGED, BELGRADE, TRAIN);
   addLink(g, SZEGED, BUCHAREST, TRAIN);
   addLink(g, SZEGED, BUDAPEST, TRAIN);
   addLink(g, VARNA, SOFIA, TRAIN);
   addLink(g, VENICE, VIENNA, TRAIN);
   addLink(g, VIENNA, BUDAPEST, TRAIN);
   addLink(g, VIENNA, PRAGUE, TRAIN);
   addLink(g, VIENNA, VENICE, TRAIN);
   addLink(g, ZURICH, MILAN, TRAIN);
   addLink(g, ZURICH, STRASBOURG, TRAIN);

   addLink(g, ADRIATIC_SEA, BARI, SEA);
   addLink(g, ADRIATIC_SEA, IONIAN_SEA, SEA);
   addLink(g, ADRIATIC_SEA, VENICE, SEA);
   addLink(g, ALICANTE, MEDITERRANEAN_SEA, SEA);
   addLink(g, AMSTERDAM, NORTH_SEA, SEA);
   addLink(g, ATHENS, IONIAN_SEA, SEA);
   addLink(g, ATLANTIC_OCEAN, BAY_OF_BISCAY, SEA);
   addLink(g, ATLANTIC_OCEAN, CADIZ, SEA);
   addLink(g, ATLANTIC_OCEAN, ENGLISH_CHANNEL, SEA);
   addLink(g, ATLANTIC_OCEAN, GALWAY, SEA);
   addLink(g, ATLANTIC_OCEAN, IRISH_SEA, SEA);
   addLink(g, ATLANTIC_OCEAN, LISBON, SEA);
   addLink(g, ATLANTIC_OCEAN, MEDITERRANEAN_SEA, SEA);
   addLink(g, ATLANTIC_OCEAN, NORTH_SEA, SEA);
   addLink(g, BARCELONA, MEDITERRANEAN_SEA, SEA);
   addLink(g, BARI, ADRIATIC_SEA, SEA);
   addLink(g, BAY_OF_BISCAY, ATLANTIC_OCEAN, SEA);
   addLink(g, BAY_OF_BISCAY, BORDEAUX, SEA);
   addLink(g, BAY_OF_BISCAY, NANTES, SEA);
   addLink(g, BAY_OF_BISCAY, SANTANDER, SEA);
   addLink(g, BLACK_SEA, CONSTANTA, SEA);
   addLink(g, BLACK_SEA, IONIAN_SEA, SEA);
   addLink(g, BLACK_SEA, VARNA, SEA);
   addLink(g, BORDEAUX, BAY_OF_BISCAY, SEA);
   addLink(g, CADIZ, ATLANTIC_OCEAN, SEA);
   addLink(g, CAGLIARI, MEDITERRANEAN_SEA, SEA);
   addLink(g, CAGLIARI, TYRRHENIAN_SEA, SEA);
   addLink(g, CONSTANTA, BLACK_SEA, SEA);
   addLink(g, DUBLIN, IRISH_SEA, SEA);
   addLink(g, EDINBURGH, NORTH_SEA, SEA);
   addLink(g, ENGLISH_CHANNEL, ATLANTIC_OCEAN, SEA);
   addLink(g, ENGLISH_CHANNEL, LE_HAVRE, SEA);
   addLink(g, ENGLISH_CHANNEL, LONDON, SEA);
   addLink(g, ENGLISH_CHANNEL, NORTH_SEA, SEA);
   addLink(g, ENGLISH_CHANNEL, PLYMOUTH, SEA);
   addLink(g, GALWAY, ATLANTIC_OCEAN, SEA);
   addLink(g, GENOA, TYRRHENIAN_SEA, SEA);
   addLink(g, HAMBURG, NORTH_SEA, SEA);
   addLink(g, IONIAN_SEA, ADRIATIC_SEA, SEA);
   addLink(g, IONIAN_SEA, ATHENS, SEA);
   addLink(g, IONIAN_SEA, BLACK_SEA, SEA);
   addLink(g, IONIAN_SEA, SALONICA, SEA);
   addLink(g, IONIAN_SEA, TYRRHENIAN_SEA, SEA);
   addLink(g, IONIAN_SEA, VALONA, SEA);
   addLink(g, IRISH_SEA, ATLANTIC_OCEAN, SEA);
   addLink(g, IRISH_SEA, DUBLIN, SEA);
   addLink(g, IRISH_SEA, LIVERPOOL, SEA);
   addLink(g, IRISH_SEA, SWANSEA, SEA);
   addLink(g, LE_HAVRE, ENGLISH_CHANNEL, SEA);
   addLink(g, LISBON, ATLANTIC_OCEAN, SEA);
   addLink(g, LIVERPOOL, IRISH_SEA, SEA);
   addLink(g, LONDON, ENGLISH_CHANNEL, SEA);
   addLink(g, MARSEILLES, MEDITERRANEAN_SEA, SEA);
   addLink(g, MEDITERRANEAN_SEA, ALICANTE, SEA);
   addLink(g, MEDITERRANEAN_SEA, ATLANTIC_OCEAN, SEA);
   addLink(g, MEDITERRANEAN_SEA, BARCELONA, SEA);
   addLink(g, MEDITERRANEAN_SEA, CAGLIARI, SEA);
   addLink(g, MEDITERRANEAN_SEA, MARSEILLES, SEA);
   addLink(g, MEDITERRANEAN_SEA, TYRRHENIAN_SEA, SEA);
   addLink(g, NANTES, BAY_OF_BISCAY, SEA);
   addLink(g, NAPLES, TYRRHENIAN_SEA, SEA);
   addLink(g, NORTH_SEA, AMSTERDAM, SEA);
   addLink(g, NORTH_SEA, ATLANTIC_OCEAN, SEA);
   addLink(g, NORTH_SEA, EDINBURGH, SEA);
   addLink(g, NORTH_SEA, ENGLISH_CHANNEL, SEA);
   addLink(g, NORTH_SEA, HAMBURG, SEA);
   addLink(g, PLYMOUTH, ENGLISH_CHANNEL, SEA);
   addLink(g, ROME, TYRRHENIAN_SEA, SEA);
   addLink(g, SALONICA, IONIAN_SEA, SEA);
   addLink(g, SANTANDER, BAY_OF_BISCAY, SEA);
   addLink(g, SWANSEA, IRISH_SEA, SEA);
   addLink(g, TYRRHENIAN_SEA, CAGLIARI, SEA);
   addLink(g, TYRRHENIAN_SEA, GENOA, SEA);
   addLink(g, TYRRHENIAN_SEA, IONIAN_SEA, SEA);
   addLink(g, TYRRHENIAN_SEA, MEDITERRANEAN_SEA, SEA);
   addLink(g, TYRRHENIAN_SEA, NAPLES, SEA);
   addLink(g, TYRRHENIAN_SEA, ROME, SEA);
   addLink(g, VALONA, IONIAN_SEA, SEA);
   addLink(g, VARNA, BLACK_SEA, SEA);
   addLink(g, VENICE, ADRIATIC_SEA, SEA);
}
