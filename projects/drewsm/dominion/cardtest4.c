/*******************************************************************************
 * Author:                  Melvin Drews
 * Date Created:            2/18/2018
 * Last Modification Date:  3/4/2018
 * Overview: unit test for the sea_hag card in dominion.c
 *
 * Input: None
 * Output: Prints to stdout the PASS/FAIL status for each test along with 
 *          a diagnostic hint; additional debugging information if
 *          DEBUG is set to 1 in dominion.h
 * 
 *  Build this test with:
 *      make cardtest4
 ******************************************************************************/

#include "unitTestCommon.h"

int main() {
    int result, currentPlayer, handPos, deckSize, testCard;
    int discardSize1, discardSize2;
    int testPlayer = 1;
    int failures = 0;
    
    //Test result explanation strings
    char *param0 = "sea_hag card";
    char *param1 = "discardCount";
    char *param2 = "expected discardCount";
    char *param3 = "discarded card was";
    char *param4 = "expected card";
    char *param5 = "condition 2 test skipped";
    char *param6 = "testPlayer top deck card";
    char param99[32];
    char* param;
    param = param99;
    
    memset(param99, 0, sizeof param99);
    sprintf(param99, "%s", param0);
    printHeader(param);
    
    //Setup the game state
    struct gameState g;
    struct gameState * game = &g;
    
    memset(game,0,sizeof(struct gameState));
    //Use the default cards specified in playdom.c
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    //setup a basic valid game
    initializeGame(2, k, 2, &g);

    //Track variables needed to evaluate resulting conditions
    deckSize = game->deckCount[testPlayer];
    discardSize1 = game->discardCount[testPlayer];
    testCard = game->deck[testPlayer][deckSize - 1];
    handPos = game->deckCount[0] - 1;
    currentPlayer = game->whoseTurn;
    
    //Ensure currentPlayer has a sea hag card
    game->deck[currentPlayer][game->deckCount[0] - 1] = sea_hag;

    result = cardEffect(sea_hag, 0, 0, 0, game, handPos, 0);
    
    /* Test conditions:
     * Condition 1: testPlayer discardCount has increased by 1
     * Condition 2: testPlayer previous deck top card is now discard top card
     * Condition 3: testPlayer's new deck top card is a curse
     */
    //Condition 1 true?
    memset(param99, 0, sizeof param99);
    discardSize2 = game->discardCount[testPlayer];
    result = myCompare(discardSize2, (discardSize1 + 1));
    sprintf(param99, "%s", param1);
    printResult(result, param, discardSize2);
    if(result) {
        failures++;
        sprintf(param99, "%s", param2);
        printResult(-1, param, (discardSize1 + 1));
    }

    //Condition 2 true?
    //No point testing condition 2 if Condition 1 was false
    if(result == 0) {
        memset(param99, 0, sizeof param99);
        result = myCompare(testCard
                ,game->discard[testPlayer][discardSize2 - 1]);
        sprintf(param99, "%s", param3);
        printResult(result, param, game->discard[testPlayer][discardSize2 - 1]);
        if(result) {
            failures++;
            memset(param99, 0, sizeof param99);
            sprintf(param99, "%s", param4);
            printResult(-1, param, testCard);
        }
    } else {
        memset(param99, 0, sizeof param99);
        sprintf(param99, "%s", param5);
        printResult(1, param, 1);
    }

    //Condition 3 true?
    //Is the testPlayer deck top card a Curse?
    memset(param99, 0, sizeof param99);
    sprintf(param99, "%s", param6);
    result = myCompare(game->deck[testPlayer][game->deckCount[testPlayer] - 1]
            , curse);
    printResult(result, param
            , game->deck[testPlayer][game->deckCount[testPlayer] - 1]);
    if(result) {
        failures++;
        memset(param99, 0, sizeof param99);
        sprintf(param99, "%s", param4);
        printResult(-1, param, curse);
    }
    printSummary(failures);
    return 0;
}