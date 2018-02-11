/*******************************************************************************
 * Author:                  Melvin Drews
 * Date Created:            1/29/2018
 * Last Modification Date:  2/5/2018
 * Overview: Unit test for the isGameOver function in dominion.c
 *
 * Input: None
 * Output: Prints to stdout the PASS/FAIL status for each test along with 
 *          a diagnostic hint
 * 
 *  Based on the testUpdateCoins.c code template provided as part of OSU CS362
 *  
 *  Build this test with:
 *      make test1
 ******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "unitTestCommon.h"
#include <string.h>
#include <stdio.h>

int main() {
    int i, j, expect, result, emptyPiles, zeroPiles, currentPile;
    int failCount = 0;
    char* param1 = "province supplyCount";
    char* param2 = "empty supply piles";
    char* param3 = "last emptied supply pile";
    char* param;
    struct gameState G;

    printf ("TESTING isGameOver():\n\n");
    
    //Test correct evaluation of province card supply empty
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    G.supplyCount[province] = 0;
    expect = 1;     //Game should be over
    param = param1;
    do {
        result = isGameOver(&G);
        result = myCompare(expect, result);
        if(result != 0) failCount++;
        printResult(result, param, G.supplyCount[province]);
                
        ++G.supplyCount[province];
        expect = 0;     //Game should not be over
    } while(G.supplyCount[province] < 2);
    //There are now some cards (at least 1) in the province pile
    
    //Test evaluation of 3 supply piles at 0 (excluding province)
    param = param2;
    emptyPiles = 4;     //The number of supply piles we want to empty
    zeroPiles = 0;      //The number of supply piles we have emptied
    currentPile = -1;    //Current supply pile being emptied
    while(zeroPiles < emptyPiles) {
        currentPile++;
        if(currentPile == province) {   //Don't empty the province pile
            continue;
        }
        G.supplyCount[currentPile] = 0;
        zeroPiles++;
    }
    // zeroPiles should = emptyPiles
    //Test isGameOver
    expect = 1;     //Game should be over
    result = isGameOver(&G);
    result = myCompare(expect, result);
    if(result != 0) failCount++;
    printResult(result, param, zeroPiles);
    
    //Test effect of each supply pile being empty, varying # of empty piles
    i = currentPile;    //Backward moving index
    while((i >= 0) && (zeroPiles >= 0)) {
        if(i == province) {
            i--;
            continue;     //province won't be empty
        }
        j = copper;  //Use as forward moving tracker
        G.supplyCount[i] = 1;
        while (j < treasure_map) {
            G.supplyCount[j+1] = 0;
            G.supplyCount[j] = 1;
            if(zeroPiles > 2) {
                expect = 1; //Game should be over
            } else {
                expect = 0; //Game should not be over
            }
        result = isGameOver(&G);
        result = myCompare(expect, result);
        printResult(result, param, zeroPiles);
        if(result != 0) {
            param = param3;
            printResult(-1, param, j+1);
            failCount++;
        }
        G.supplyCount[j+1] = 1;
        j++;
        }
        if(i > 0) i--;
        zeroPiles--;
    }
    
    printSummary(failCount);

    return 0;
}