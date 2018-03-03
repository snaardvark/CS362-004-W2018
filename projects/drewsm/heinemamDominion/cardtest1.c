/*******************************************************************************
 * Author:                  Melvin Drews
 * Date Created:            2/18/2018
 * Last Modification Date:  2/18/2018
 * Overview: unit test for the smithyEffect function in dominion.c
 *
 * Input: None
 * Output: Prints to stdout the PASS/FAIL status for each test along with 
 *          a diagnostic hint; additional debugging information if
 *          DEBUG is set to 1 in dominion.h
 * 
 *  Build this test with:
 *      make cardtest1
 ******************************************************************************/

#include "unitTestCommon.h"

int main() {
    int i, discardSize, deckSize, playedCards, lastPlayed;
    int handSize, result, test1, handPos, val1, val2, val3;
    int smithyCards1, smithyCards2;
    int currentPlayer;
    int failures = 0;
    
    //Tracking for current values
    
        
    //Test result explanation strings
    char *param0 = "smithy card";
    char *param1 = "pre-test handCount";
    char *param2 = "smithy hand position";
    char *param3 = "deck or discard reduced";
    char *param4 = "deckCount";
    char *param5 = "discardCount";
    char *param6 = "played card count";
    char *param7 = "lastPlayed should be 13, is";
    char *param8 = "0 smithy cards trashed, is";
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
    currentPlayer = game->whoseTurn;

    //Insert smithy card at a known position of player hand
    handPos = game->handCount[currentPlayer] - 1;
    game->hand[currentPlayer][handPos] = smithy;

    //Track variables needed to evaluate resulting conditions
    handSize = game->handCount[currentPlayer];
    discardSize = game->discardCount[currentPlayer];
    deckSize = game->deckCount[currentPlayer];
    playedCards = game->playedCardCount;
    lastPlayed = game->playedCards[currentPlayer];
    //Count total smithy cards in the game;
    smithyCards1 = game->supplyCount[smithy];
    smithyCards2 = 0;
    for(i = 0; i < game->handCount[currentPlayer]; i++) {
        if(game->hand[currentPlayer][i] == smithy) smithyCards1++;
    }
    for(i = 0; i < game->deckCount[currentPlayer]; i++) {
        if(game->deck[currentPlayer][i] == smithy) smithyCards1++;
    }
    for(i = 0; i < game->discardCount[currentPlayer]; i++) {
        if(game->discard[currentPlayer][i] == smithy) smithyCards1++;
    }
    if(game->playedCards[game->playedCardCount] == smithy) smithyCards1++;

    result = cardEffect(smithy, 0, 0, 0, game, handPos, 0);

    /* Test conditions:
     * Condition 1: 3 additional cards are added to currentPlayer hand.
     * Condition 2: 3 cards removed from the total number of cards in
     *              deckCount + discardCount.
     * Condition 3: Smithy is added to the playedCards pile
     */
    //Condition 1 true?
    memset(param99, 0, sizeof param99);
    test1 = myCompare((handSize + 2), game->handCount[currentPlayer]);
    sprintf(param99, "%s", param1);
    if(test1) {
        printResult(1, param, handSize);
    } else {
        printResult(0, param, handSize);
    }
    if(test1) {
        failures++;
        memset(param99, 0, sizeof param99);
        sprintf(param99, "%s", param2);
        printResult(-1, param, handPos);
    }

    //Condition 2 true?
    val1 = game->deckCount[currentPlayer];
    val2 = game->discardCount[currentPlayer];
    val3 = val1 + val2;
    memset(param99, 0, sizeof param99);
    test1 = myCompare((deckSize + discardSize - 3), val3);
    sprintf(param99, "%s", param3);
    if(test1) {
        printResult(1, param, (deckSize + discardSize - val3));
    } else {
        printResult(0, param, (deckSize + discardSize - val3));
    }
    if(test1) {
        failures++;
        memset(param99, 0, sizeof param99);
        sprintf(param99, "%s = %i, %s", param4, val1, param5);
        printResult(-1, param, val2);
    }

    //Condition 3 true?
    //Are the number of cards & last card played both correct?
    val1 = myCompare(game->playedCardCount, (playedCards + 1));
    val2 = myCompare(lastPlayed, game->playedCards[currentPlayer]);
    memset(param99, 0, sizeof param99);
    sprintf(param99, "%s", param6);
    if(val1) {
        printResult(1, param, game->playedCardCount);
    } else {
        printResult(0, param, game->playedCardCount);
    }
    smithyCards2 = game->supplyCount[smithy];
    for(i = 0; i < game->handCount[currentPlayer]; i++) {
        if(game->hand[currentPlayer][i] == smithy) smithyCards2++;
    }
    for(i = 0; i < game->deckCount[currentPlayer]; i++) {
        if(game->deck[currentPlayer][i] == smithy) smithyCards2++;
    }
    for(i = 0; i < game->discardCount[currentPlayer]; i++) {
        if(game->discard[currentPlayer][i] == smithy) smithyCards2++;
    }
    if(game->playedCards[game->playedCardCount] == smithy) smithyCards2++;
    val3 = myCompare(smithyCards1, smithyCards2);
    if(val1 || val2) {
        failures++;
        memset(param99, 0, sizeof param99);
        sprintf(param99, "%s", param7);
        printResult(2, param, game->playedCards[currentPlayer]);
        if(val3) {
            memset(param99, 0, sizeof param99);
            sprintf(param99, "%s", param8);
            printResult(-1, param, (smithyCards1 - smithyCards2));
        }
    }
    printSummary(failures);
    return 0;
}
