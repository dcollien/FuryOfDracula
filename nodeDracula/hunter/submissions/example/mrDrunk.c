#include "game.h"
#include "HunterView.h"
#include "hunter.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *cityCodes[] = {"AL", "AM", "AT", "BA", "BI", "BE", "BR", "BO", "BU", "BC",
                         "BD", "CA", "CG", "CD", "CF", "CO", "CN", "DU", "ED", "FL",
                         "FR", "GA", "GW", "GE", "GO", "GR", "HA", "JM", "KL", "LE",
                         "LI", "LS", "LV", "LO", "MA", "MN", "MR", "MI", "MU", "NA",
                         "NP", "NU", "PA", "PL", "PR", "RO", "SA", "SN", "SR", "SJ",
                         "SO", "ST", "SW", "SZ", "TO", "VA", "VR", "VE", "VI", "ZA",
                         "ZU", "NS", "EC", "IS", "AO", "BB", "MS", "TS", "IO", "AS",
                         "BS", "C?", "S?", "HI", "D1", "D2", "D3", "D4", "D5", "TP"};                      

void decideMove (HunterView gameState) {

   hunterCode currentHunter = HunterView_CurrentHunter(gameState);
   int roundNumber = HunterView_CurrentRound(gameState);
   int length;
   int i = 0;
   srand(time(NULL)+(roundNumber*5)+currentHunter);
   if (roundNumber != 0) {
      locationCode currentLocation = HunterView_HunterLocation(gameState, currentHunter);
      locationCode *moves = allLegalMoves(currentLocation, roundNumber, currentHunter, &length);
      for (i = 0; i < length; i++) {
         printf ("%s\n", cityCodes[moves[i]]);
      }
      registerBestPlay( cityCodes[moves[rand()%length]], "I Wanna Stake You Dracula <3" );
      free(moves);
   } else { 
      registerBestPlay( cityCodes[rand()%NUM_MAP_LOCATIONS], "I Wanna Stake You Dracula <3" );
   }
 
}
