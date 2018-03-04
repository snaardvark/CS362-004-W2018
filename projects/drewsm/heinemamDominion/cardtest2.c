/*******************************************************************************
 * Author:                  Melvin Drews
 * Date Created:            2/12/2018
 * Last Modification Date:  3/3/2018
 * Overview: unit test for the adventurerEffect function in dominion.c
 *
 * Input: None
 * Output: Prints to stdout the PASS/FAIL status for each test along with 
 *          a diagnostic hint; additional debugging information if
 *          DEBUG is set to 1 in dominion.h
 * 
 *  Build this test with:
 *      make cardtest2
 ******************************************************************************/

#include "unitTestCommon.h"
#include "randTestCommon.h"

int main() {
    int result, i, discardSize, deckSize;
    //int handSize, found, val, undecked;
    int handSize, val1, undecked;
    int currentPlayer;
    int failures = 0;
    
    //Tracking for current values
//    int deckTreasure, discardTreasure;
    int deckTreasure;
//    int deckCopper, deckSilver, deckGold;
//    int discardCopper=0, discardSilver=0, discardGold=0;
    
    //Where they were found in deck
    int t1DeckPos, t2DeckPos;
    
    //Test result explanation strings
    char *param0 = "adventurer card";
    char *param1 = "deck treasure";
    char *param2 = "available treasure";
    char *param3 = "new handSize";
    char *param4 = "adding treasure1 to hand";
    //char *param5 = "adding treasure2 to hand";
    char *param6 = "removing cards from deck";
    char *param7 = "discarding drawn cards";
    char *param8 = "discard size";
    char *param9 = "deck size";
    char param99[32];
    char* param;
    param = param99;
    
    memset(param99, 0, sizeof param99);
    sprintf(param99, "%s", param0);
    printHeader(param);
    
    //Setup the game state
    struct gameState g;
    struct gameState * game = &g;
   
    deckTreasure = 0;
    undecked = 0;

    memset(game,0,sizeof(struct gameState));
    //Use the default cards specified in playdom.c
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    //setup a basic valid game
    initializeGame(2, k, 2, &g);

    currentPlayer = game->whoseTurn;    //record the currentPlayer

    t1DeckPos = -1;
    t2DeckPos = -1;
    
    for(i = game->deckCount[currentPlayer] - 1; i >= 0; i--) {
        if(game->deck[currentPlayer][i] == copper) {
            if(t1DeckPos == -1) {   //Is treasure position marked yet?
            t1DeckPos = i;      //1st treasure in deck is here
            } else if(t2DeckPos == -1) {    //Is 2nd treasure marked?
                t2DeckPos = i;      //2nd treasure in deck is here
            }
        }
    }

    deckTreasure = 3;
//    discardTreasure = discardCopper + discardSilver + discardGold;
    handSize = game->handCount[currentPlayer];
    deckSize = game->deckCount[currentPlayer];
    discardSize = game->discardCount[currentPlayer];

    //run the card effect function
    result = cardEffect(adventurer, 0, 0, 0, game, 0, 0);

    /*Test Conditions:
     * Condition1: currentPlayer handCount should have increased by 2
     * Condition 2: 1st two treasure cards from deck should be pulled into
     *      currentPlayer hand
     * Condition 3: cards up to and including the 2 treasure cards have
     *      been removed from currentPlayer deck
     * Condition 4: cards removed from currentPlayer deck have been
     *      added to currentPlayer discard pile
     * */
    memset(param99, 0, sizeof param99);
    //Condition1 true?
    //Test if handCount increased by exactly the right number
    val1 = 2;
    result = myCompare((handSize + val1), game->handCount[currentPlayer]);
    sprintf(param99, "%s", param2);
    if(result) {
        printResult(1, param, deckTreasure);
        failures++;
        memset(param99, 0, sizeof param99);
        sprintf(param99, "%s", param3);
        printResult(-1, param, (handSize + val1));
    } else {
        printResult(0, param, deckTreasure);
    }

    //Condition2 true?
    //Test if treasure1 was added to hand
    memset(param99, 0, sizeof param99);
    result = myCompare(game->hand[currentPlayer][handSize], copper);
    sprintf(param99, "%s", param4);
    if(result) {
        printResult(1, param, copper);
        failures++;
        memset(param99, 0, sizeof param99);
        sprintf(param99, "%s", param1);
        printResult(-1, param, deckTreasure);
    } else {
        printResult(0, param, copper);
    }
    

    //Condition 3 true?
    //Test if deckCount was reduced by number of cards drawn
    memset(param99, 0, sizeof param99);
    result = myCompare(game->deckCount[currentPlayer], t2DeckPos);
    sprintf(param99, "%s", param6);
    undecked = deckSize - t2DeckPos;
    if(result) {
        printResult(1, param, undecked);
        failures++;
        memset(param99, 0, sizeof param99);
        sprintf(param99, "%s", param9);
        printResult(-1, param, (deckSize - undecked));
    } else {
        printResult(0, param, undecked);
    }

    //Condition 4 true?
    //Number of treasure cards pulled in the hand
    val1 = game->handCount[currentPlayer] - handSize;
    //Calculate number of deck cards discarded
    if(deckTreasure <= 2) {
        undecked = deckSize;
    } else {
        //Number of cards that should've been pulled from deck
        undecked = deckSize - game->deckCount[currentPlayer];
    }
    if(myCompare(discardSize, game->discardCount[currentPlayer])) {
        undecked += (game->discardCount[currentPlayer] - discardSize);
    }
    
    memset(param99, 0, sizeof param99);
    result = myCompare((discardSize + undecked)
            ,game->discardCount[currentPlayer]);
    sprintf(param99, "%s", param7);
    if(result) {
        printResult(1, param, undecked);
        failures++;
        memset(param99, 0, sizeof param99);
        sprintf(param99, "%s", param8);
        printResult(-1, param, game->discardCount[currentPlayer]);
    } else {
        printResult(0, param, undecked);
    }
    printSummary(failures);
    return 0;
}