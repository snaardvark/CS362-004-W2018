/*******************************************************************************
 * Author:                  Melvin Drews
 * Date Created:            2/12/2018
 * Last Modification Date:  2/18/2018
 * Overview: random test suite for the adventurerEffect function in dominion.c
 *
 * Input: None
 * Output: Prints to stdout the PASS/FAIL status for each test along with 
 *          a diagnostic hint; additional debugging information if
 *          DEBUG is set to 1 in dominion.h
 * 
 *  Build this test with:
 *      make randomtestadventurer
 ******************************************************************************/

#include "randTestCommon.h"

int main() {
    int runs, i, discardSize, deckSize;
    int handSize, result, found, val, undecked;
    int currentPlayer;
    int failures = 0;
    
    //Tracking for current values
    int deckTreasure, discardTreasure;
    int handCopper, handSilver, handGold;
    int deckCopper, deckSilver, deckGold;
    int discardCopper=0, discardSilver=0, discardGold=0;
    
    //The 2 treasures that should be pulled into currentPlayer hand
    int treasure1=-1, treasure2=-1; //What the treasure cards are
    //Where they were found in deck or discard pile
    int t1DeckPos, t2DeckPos, t1DiscPos, t2DiscPos;
    
    //Test result explanation strings
    char *param1 = "deck treasure";
    char *param2 = "available treasure";
    char *param3 = "new handSize";
    char *param4 = "adding treasure1 to hand";
    char *param5 = "adding treasure2 to hand";
    char *param6 = "removing cards from deck";
    char *param7 = "discarding drawn cards";
    char *param8 = "discard size";
    char *param9 = "deck size";
    char param99[32];
    char* param;
    param = param99;
    
    //Setup the game state
    struct gameState g;
    struct gameState * game = &g;
    
    PlantSeeds(-1);
    
    //Run the test suite 1000 times
    for(runs = 0; runs < 1000; runs++) {
        deckTreasure = 0;
        discardTreasure = 0;
        undecked = 0;
        handCopper = 0;
        handSilver = 0;
        handGold = 0;
        deckCopper = 0;
        deckSilver = 0;
        deckGold = 0;
        discardCopper = 0;
        discardSilver = 0;
        discardGold = 0;
        treasure1=-1;
        treasure2=-1;
        
        memset(game,0,sizeof(struct gameState));
        randGame(game);

        //Select a random player. This will test if the card effect works
        //differently depending on player number
        randPlayer(game);
        
        currentPlayer = game->whoseTurn;    //record the currentPlayer

        //Randomize the cards in currentPlayer deck, using cards that are in play
        randomizeCards(game, currentPlayer);
        
        //We need to know how many copper, silver, and gold are in currentPlayer
        //deck, hand, and discard, as well as supply to test the card effect
        for(i = 0; i < game->handCount[currentPlayer]; i++) {
            switch(game->hand[currentPlayer][i]) {
                case copper:
                    handCopper++;
                    break;
                case silver:
                    handSilver++;
                    break;
                case gold:
                    handGold++;
            }
        }
        t1DeckPos = -1;
        t2DeckPos = -1;
        t1DiscPos = -1;
        t2DiscPos = -1;
        
        for(i = game->deckCount[currentPlayer] - 1; i >= 0; i--) {
            found = 0;
            switch(game->deck[currentPlayer][i]) {
                case copper:
                    deckCopper++;
                    setTreasure(&treasure1, &treasure2, copper);
                    found++;
                    break;
                case silver:
                    deckSilver++;
                    setTreasure(&treasure1, &treasure2, silver);
                    found++;
                    break;
                case gold:
                    deckGold++;
                    setTreasure(&treasure1, &treasure2, gold);
                    found++;
            }
            if(found) {
                if(t1DeckPos == -1) {   //Is treasure position marked yet?
                    t1DeckPos = i;      //1st treasure in deck is here
                } else if(t2DeckPos == -1) {    //Is 2nd treasure marked?
                    t2DeckPos = i;      //2nd treasure in deck is here
                }
            }
        }
        for(i = game->discardCount[currentPlayer] - 1; i >= 0; i--) {
            found = 0;
            switch(game->discard[currentPlayer][i]) {
                case copper:
                    discardCopper++;
                    setTreasure(&treasure1, &treasure2, copper);
                    found++;
                    break;
                case silver:
                    discardSilver++;
                    setTreasure(&treasure1, &treasure2, silver);
                    found++;
                    break;
                case gold:
                    discardGold++;
                    setTreasure(&treasure1, &treasure2, gold);
                    found++;
            }
            if(found) {
                if(t1DiscPos == -1) {   //Is treasure position marked yet?
                    t1DiscPos = i;      //1st treasure in discard pile is here
                } else if(t2DiscPos == -1) {    //Is 2nd treasure marked?
                    t2DiscPos = i;      //2nd treasure in discard pile is here
                }
            }
        }
        
        deckTreasure = deckCopper + deckSilver + deckGold;
        discardTreasure = discardCopper + discardSilver + discardGold;
        handSize = game->handCount[currentPlayer];
        deckSize = game->deckCount[currentPlayer];
        discardSize = game->discardCount[currentPlayer];

        //run the card effect function
        adventurerEffect(game, currentPlayer);

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
        if((deckTreasure + discardTreasure) >= 2) {
            val = 2;
        } else if((deckTreasure + discardTreasure) == 1) {
            val = 1;
        } else val = 0;
        result = myCompare((handSize + val), game->handCount[currentPlayer]);
        sprintf(param99, "%s", param2);
        printResult(result, param, (deckTreasure + discardTreasure));
        if(result) {
            failures++;
            memset(param99, 0, sizeof param99);
            sprintf(param99, "%s", param3);
            printResult(2, param, (handSize + val));
//            if(DEBUG) {
//                printf("DEBUG: original deckCount was = %i\n", deckSize);
//                printf("DEBUG: original discardCount was = %i\n", discardSize);
//                printf("DEBUG: original handSize was = %i\n", handSize);
//                printf("DEBUG: current handCount = %i\n", game->handCount[currentPlayer]);
//                printVars(game);
//            }
        }

        //Condition2 true?
        //Due to possible shuffling, test only works if treasure in deck > 0
        if((treasure1 > -1) && (t1DeckPos > -1)){
            //Test if treasure1 was added to hand
            memset(param99, 0, sizeof param99);
            result = myCompare(game->hand[currentPlayer][handSize], treasure1);
            sprintf(param99, "%s", param4);
            printResult(result, param, treasure1);
            if(result) {
                failures++;
                memset(param99, 0, sizeof param99);
                sprintf(param99, "%s", param1);
                printResult(2, param, deckTreasure);
            }
        }
        //Due to possible shuffling, test only works if treasure in deck > 1
        if((treasure2 > -1) && (t2DeckPos > -1)) {
            //Test if treasure2 was added to hand
            memset(param99, 0, sizeof param99);
            result = myCompare(game->hand[currentPlayer][handSize + 1], treasure2);
            sprintf(param99, "%s", param5);
            printResult(result, param, treasure2);
            if(result) {
                failures++;
                memset(param99, 0, sizeof param99);
                sprintf(param99, "%s", param1);
                printResult(2, param, deckTreasure);
            }
        }

        //Condition 3 true?
        //Test if deckCount was reduced by number of cards drawn
        //Due to possible shuffling, test only works if treasure in deck > 1
        if(deckTreasure > 1) {
            memset(param99, 0, sizeof param99);
            result = myCompare(game->deckCount[currentPlayer], t2DeckPos);
            sprintf(param99, "%s", param6);
            undecked = deckSize - t2DeckPos;
            printResult(result, param, undecked);
            if(result) {
                failures++;
                memset(param99, 0, sizeof param99);
                sprintf(param99, "%s", param9);
                printResult(2, param, (deckSize - undecked));
            }
        }

        //Condition 4 true?
        //Test if non-treasure cards drawn from deck were added to discard pile
        //Calculate number of treasure cards that should've been kept
        if((deckTreasure + discardTreasure) >= 2) {
            val = 2;
        } else if ((deckTreasure + discardTreasure) == 1) {
            val = 1;
        } else {
            val = 0;
        }
        //Calculate number of deck cards discarded
        if(deckTreasure <= 2) {
            undecked = deckSize;
        } else {
            undecked = deckSize - t2DeckPos;
        }
        val = undecked - val;   //number that should've been added to discard
        memset(param99, 0, sizeof param99);
        result = myCompare(game->discardCount[currentPlayer],
                (discardSize + undecked));
        sprintf(param99, "%s", param7);
        printResult(result, param, undecked);
        if(result) {
            failures++;
            memset(param99, 0, sizeof param99);
            sprintf(param99, "%s", param8);
            printResult(2, param, (discardSize + val));
//            if(DEBUG) {
//                printf("\tActural current discardCount = %i\n",
//                        game->discardCount[currentPlayer]);
//            }
        }
    }
    printSummary(failures);
    return 0;
}