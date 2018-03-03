/*******************************************************************************
 * Author:                  Melvin Drews
 * Date Created:            2/4/2018
 * Last Modification Date:  2/4/2018
 * Overview: Unit test for the numHandCards function in dominion.c
 *
 * Input: None
 * Output: Prints to stdout the PASS/FAIL status for each test along with 
 *          a diagnostic hint
 * 
 *  Based on the testUpdateCoins.c code template provided as part of OSU CS362
 *  
 *  Build this test with:
 *      make test3
 ******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "unitTestCommon.h"
#include <string.h>
#include <stdio.h>

int main() {
    int handCards, player, expect, result;
    int failCount = 0;
    char* param0 = "numHandCards function";
    char* param1 = "player";
    char param2[32];
    char* param;
    param = param2;
    struct gameState G;
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    
    memset(param2, 0, sizeof param2);
    sprintf(param2, "%s", param0);
    printHeader(param);
    
    //Run the test for each player value possible in a valid game state
    for(player = 0; player < MAX_PLAYERS; player++) {
        G.whoseTurn = player;
        //Run test for each possible handCount in a valid game state
        for(handCards = 0; handCards <= MAX_HAND; handCards++) {
            G.handCount[player] = handCards;
            memset(param2, 0, sizeof param2);
            sprintf(param2, "%s %i and handCount", param1, player);
            expect = handCards;
            result = numHandCards(&G);
            result = myCompare(expect, result);
            if(result != 0) failCount++;
            printResult(result, param, handCards);
        }
    }
    
    printSummary(failCount);

    return 0;
}