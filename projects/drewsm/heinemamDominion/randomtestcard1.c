/*******************************************************************************
 * Author:                  Melvin Drews
 * Date Created:            2/18/2018
 * Last Modification Date:  2/18/2018
 * Overview: random test suite for the smithyEffect function in dominion.c
 *
 * Input: None
 * Output: Prints to stdout the PASS/FAIL status for each test along with 
 *          a diagnostic hint; additional debugging information if
 *          DEBUG is set to 1 in dominion.h
 * 
 *  Build this test with:
 *      make randomtestcard1
 ******************************************************************************/

#include "randTestCommon.h"

int main() {
    int runs, i, discardSize, deckSize, playedCards, lastPlayed;
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
    
    PlantSeeds(-1);
    
    //Run the test suite 1000 times
    for(runs = 0; runs < 1000; runs++) {
        memset(game,0,sizeof(struct gameState));
        randGame(game);

        //Select a random player. This will test if the card effect works
        //differently depending on player number
        randPlayer(game);
        
        currentPlayer = game->whoseTurn;    //record the currentPlayer

        //Randomize the cards in currentPlayer deck, using cards that are in play
        randomizeCards(game, currentPlayer);
        
        //Check if smithy is already in currenPlayer hand
        //If yes, handPos holds index of the first one found
        handPos = findHandPos(game, smithy, currentPlayer);
        if(handPos == -1) { //If smithy not found, add it into the hand
            //choose a random hand position to insert smithy
            handPos = getRandom(game->handCount[currentPlayer] - 1);
            game->hand[currentPlayer][handPos] = smithy;
        }
        
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
        //result = smithyEffect(game, handPos, currentPlayer);
        
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
            failures++;
            memset(param99, 0, sizeof param99);
            sprintf(param99, "%s", param2);
            printResult(2, param, handPos);
        } else {
            printResult(0, param, handSize);
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
            failures++;
            memset(param99, 0, sizeof param99);
            sprintf(param99, "%s = %i, %s", param4, val1, param5);
            printResult(2, param, val2);
        } else {
            printResult(0, param, (deckSize + discardSize - val3));
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
        if(val1 || (val2 == 0)) {
            failures++;
            memset(param99, 0, sizeof param99);
            sprintf(param99, "%s", param7);
            printResult(1, param, game->playedCards[currentPlayer]);
            if(val3) {
                memset(param99, 0, sizeof param99);
                sprintf(param99, "%s", param8);
                printResult(2, param, (smithyCards1 - smithyCards2));
            }
        }
    }
    printSummary(failures);
    return 0;
}
