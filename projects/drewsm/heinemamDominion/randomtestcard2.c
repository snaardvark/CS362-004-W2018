/*******************************************************************************
 * Author:                  Melvin Drews
 * Date Created:            2/18/2018
 * Last Modification Date:  2/18/2018
 * Overview: random test suite for the embargoEffect function in dominion.c
 *
 * Input: None
 * Output: Prints to stdout the PASS/FAIL status for each test along with 
 *          a diagnostic hint; additional debugging information if
 *          DEBUG is set to 1 in dominion.h
 * 
 *  Build this test with:
 *      make randomtestcard2
 ******************************************************************************/

#include "randTestCommon.h"

int main() {
    int runs, result, i, j, choice, inPlay, test1, handPos, val1;
    int coinCount;
    int embargoCards1, embargoCards2;   //pre and post-execution of card effect
    int eTokens = 0;
    int currentPlayer;
    int failures = 0;
    
    //Tracking for current values
    
        
    //Test result explanation strings
    char *param0 = "embargo card";
    char *param1 = "coin count";
    char *param2 = "embargo cards trashed";
    char *param3 = "embargo tokens";
    char *param4 = "embargo added to unused supply";
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
    
    /* Run the test suite 5000 times. We need more test runs for this test
     * because of the high max number of embargo supply cards set for
     * randomness.
     */
    for(runs = 0; runs < 5000; runs++) {
        memset(game,0,sizeof(struct gameState));
        randGame(game);

        //Select a random player. This will test if the card effect works
        //differently depending on player number
        randPlayer(game);
        
        currentPlayer = game->whoseTurn;    //record the currentPlayer

        //Randomize cards in currentPlayer deck using cards that are in play
        randomizeCards(game, currentPlayer);
        
        //Check if embargo is already in currenPlayer hand
        //If yes, handPos holds index of the first one found
        handPos = findHandPos(game, embargo, currentPlayer);
        if(handPos == -1) { //If embargo not found, add it into the hand
            //choose a random hand position to insert smithy
            handPos = getRandom(game->handCount[currentPlayer] - 1);
            game->hand[currentPlayer][handPos] = embargo;
        }
        //set a random number of coins for the currentPlayer
        game->coins = getRandom(100);
        //set a random number of embargo cards in the supply pile
        game->supplyCount[embargo] = getRandom(MAX_DECK);
        
        //Track variables needed to evaluate resulting conditions
        coinCount = game->coins;
        //Count embargo cards in use in the game
        embargoCards1 = game->supplyCount[embargo];
        for(i = 0; i < game->numPlayers; i++) {
            for(j = 0; j < game->deckCount[i]; j++) {
                if(game->deck[i][j] == embargo) embargoCards1++;
            }
            for(j = 0; j < game->discardCount[i]; j++) {
                if(game->discard[i][j] == embargo) embargoCards1++;
            }
            for(j = 0; j < game->handCount[i]; j++) {
                if(game->hand[i][j] == embargo) embargoCards1++;
            }
        }
        for(i = 0; i < game->playedCardCount; i++) {
            if(game->playedCards[i] == embargo) embargoCards1++;
        }
        
        choice = getRandom(treasure_map);  //The supply to put embargo token on
        
        //Test if the chosen supply is in play
        if(game->supplyCount[choice] > 0) {
            inPlay = 1;
        } else {
            inPlay = 0;
        }
        if(inPlay) {
            //Set a random number of embargo tokens on the chosen supply
            eTokens = getRandom(10);
            game->embargoTokens[choice] = eTokens;
        }
        
        result = cardEffect(embargo, choice, 0, 0, game, handPos, 0);
        //result = embargoEffect(choice, game, handPos, currentPlayer);
        
        /* Test conditions:
         * Condition 1: Player received two coins
         * Condition 2: The Embargo card is trashed (removed from play)
         * Condition 3: Embargo token is added to the specified supply pile
         *              only if the supply is in play
         */
        //Condition 1 true?
        memset(param99, 0, sizeof param99);
        test1 = myCompare((coinCount + 2), game->coins);
        sprintf(param99, "%s", param1);
        printResult(test1, param, game->coins);
        if(test1) {
            failures++;
            printResult(2, param, (coinCount + 2));
        }
        
        //Condition 2 true?
        //Count embargo cards currently in use in the game
        embargoCards2 = game->supplyCount[embargo];
        for(i = 0; i < game->numPlayers; i++) {
            for(j = 0; j < game->deckCount[i]; j++) {
                if(game->deck[i][j] == embargo) embargoCards2++;
            }
            for(j = 0; j < game->discardCount[i]; j++) {
                if(game->discard[i][j] == embargo) embargoCards2++;
            }
            for(j = 0; j < game->handCount[i]; j++) {
                if(game->hand[i][j] == embargo) embargoCards2++;
            }
        }
        for(i = 0; i < game->playedCardCount; i++) {
            if(game->playedCards[i] == embargo) embargoCards2++;
        }
        memset(param99, 0, sizeof param99);
        if(inPlay) {
            test1 = myCompare((embargoCards1 - 1), embargoCards2);
        } else {
            test1 = myCompare(embargoCards1, embargoCards2);
        }
        sprintf(param99, "%s", param2);
        printResult(test1, param, (embargoCards1 - embargoCards2));
        if(test1) {
            failures++;
            memset(param99, 0, sizeof param99);
            if(inPlay) {
                val1 = 1;
            } else {
                val1 = 0;
            }
            printResult(2, param, val1);
        }
        
        //Condition 3 true?
        //Is the embargo token count correct on the chosen supply pile?
        memset(param99, 0, sizeof param99);
        sprintf(param99, "%s", param3);
        if(inPlay) {
            test1 = myCompare((eTokens + 1), game->embargoTokens[choice]);
        } else {
            test1 = myCompare(0, game->embargoTokens[choice]);
        }
        printResult(test1, param, game->embargoTokens[choice]);
        if(test1) {
            failures++;
            if(inPlay) {
                printResult(2, param, (eTokens + 1));
            } else {
                memset(param99, 0, sizeof param99);
                sprintf(param99, "%s", param4);
                printResult(2, param, 0);
            }
        }
    }
    printSummary(failures);
    return 0;
}