/*******************************************************************************
 * Author:                  Melvin Drews
 * Date Created:            2/4/2018
 * Last Modification Date:  2/4/2018
 * Overview: Unit test for the updateCoins function in dominion.c
 *
 * Input: None
 * Output: Prints to stdout the PASS/FAIL status for each test along with 
 *          a diagnostic hint
 * 
 *  Based on the testUpdateCoins.c code template provided as part of OSU CS362
 *  
 *  Build this test with:
 *      make test4
 ******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "unitTestCommon.h"
#include <string.h>
#include <stdio.h>

int main() {
    int bonus, coins, expect, result;
    int failCount = 0;
    char* param0 = "updateCoins function";
    char param1[52];
    char param2[22];
    char* param3 = "copper,";
    char* param4 = "copper, silver,";
    char* param5 = "copper, silver, gold,";
    char* param;
    struct gameState G;
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    
    memset(param1, 0, sizeof param1);
    sprintf(param1, "%s", param0);
    param = param1;
    printHeader(param);
    
    G.handCount[0] = 10;    //Set the handCount for player0
    
    /**************************************************************************
     * Testing with different values for coins simulates the effect of
     * playing multiple action cards, where one action card may add some
     * number of coins to see if this is accurately reflected when later
     * action cards are played
     **************************************************************************/
    for(coins = 0; coins <= 1; coins++) {
        for(bonus = 0; bonus <= 1; bonus++) {
            G.coins = coins;    //Set the value in the game state
            G.hand[0][1] = -1;  //Clear silver out of the player hand
            G.hand[0][2] = -1;  //Clear gold out of the player hand
            G.hand[0][0] = copper;  //Put 1 copper in player0's hand
            expect = coins + bonus + 1;

            //Run Test
            result = updateCoins(0, &G, bonus);
            result = G.coins;
            result = myCompare(expect, result);
            if(result != 0) failCount++;
            memset(param1, 0, sizeof param1);
            memset(param2, 0, sizeof param2);
            sprintf(param2, "%s", param3);
            sprintf(param1, "initial coins = %i, %s and bonus", coins, param2);
            param = param1;
            printResult(result, param, bonus);

            G.hand[0][1] = silver;  //Put 1 silver in player0's hand
            expect += 2;

            //Run Test
            result = updateCoins(0, &G, bonus);
            result = G.coins;
            result = myCompare(expect, result);
            if(result != 0) failCount++;
            memset(param1, 0, sizeof param1);
            memset(param2, 0, sizeof param2);
            sprintf(param2, "%s", param4);
            sprintf(param1, "initial coins = %i, %s and bonus", coins, param2);
            param = param1;
            printResult(result, param, bonus);

            G.hand[0][2] = gold;  //Put 1 gold in player0's hand
            expect += 3;
            
            //Run Test
            result = updateCoins(0, &G, bonus);
            result = G.coins;
            result = myCompare(expect, result);
            if(result != 0) failCount++;
            memset(param1, 0, sizeof param1);
            memset(param2, 0, sizeof param2);
            sprintf(param2, "%s", param5);
            sprintf(param1, "initial coins = %i, %s and bonus", coins, param2);
            param = param1;
            printResult(result, param, bonus);
        }
    }

    printSummary(failCount);

    return 0;
}