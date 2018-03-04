/*******************************************************************************
 * Author:                  Melvin Drews
 * Date Created:            2/18/2018
 * Last Modification Date:  3/4/2018
 * Overview: unit test for the embargoEffect function in dominion.c
 *
 * Input: None
 * Output: Prints to stdout the PASS/FAIL status for each test along with 
 *          a diagnostic hint; additional debugging information if
 *          DEBUG is set to 1 in dominion.h
 * 
 *  Build this test with:
 *      make cardtest3
 ******************************************************************************/

#include "unitTestCommon.h"

int main() {
    int result, i, j, test1, handPos, val1;
    int coinCount;
    int embargoCards1, embargoCards2;   //pre and post-execution of card effect
    int eTokens = 0;
    int currentPlayer;
    int failures = 0;
    int embargoSupp = adventurer;  //The supply to put embargo token on
    
    //Test result explanation strings
    char *param0 = "embargo card";
    char *param1 = "coin count";
    char *param2 = "embargo cards trashed";
    char *param3 = "embargo tokens";
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

    currentPlayer = game->whoseTurn;        //record the currentPlayer
    game->embargoTokens[embargoSupp] = 0;   //Make sure we know the value

    //Add embargo into the currentPlayer hand
    //choose a random hand position to insert smithy
    handPos = game->handCount[currentPlayer] - 1;
    game->hand[currentPlayer][handPos] = embargo;
        
    //Ensure we know the number of coins for the currentPlayer
    game->coins = 0;
    //set a known number of embargo cards in the supply pile
    game->supplyCount[embargo] = 2;

    //Track variables needed to evaluate resulting conditions
    coinCount = game->coins;
    //Count embargo cards in use in the game (Should = 3)
    embargoCards1 = game->supplyCount[embargo] + 1; //2 in supply pile, 1 in hand

    result = cardEffect(embargo, embargoSupp, 0, 0, game, handPos, 0);

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
    test1 = myCompare((embargoCards1 - 1), embargoCards2);
    sprintf(param99, "%s", param2);
    printResult(test1, param, (embargoCards1 - embargoCards2));
    if(test1) {
        failures++;
        memset(param99, 0, sizeof param99);
        val1 = 1;
        printResult(2, param, val1);
    }

    //Condition 3 true?
    //Is the embargo token count correct on the chosen supply pile?
    memset(param99, 0, sizeof param99);
    sprintf(param99, "%s", param3);
    test1 = myCompare((eTokens + 1), game->embargoTokens[embargoSupp]);
    printResult(test1, param, game->embargoTokens[embargoSupp]);
    if(test1) {
        failures++;
        printResult(2, param, (eTokens + 1));
    }
    printSummary(failures);
    return 0;
}