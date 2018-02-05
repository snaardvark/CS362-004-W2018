/*******************************************************************************
 * Author:                  Melvin Drews
 * Date Created:            2/3/2018
 * Last Modification Date:  2/4/2018
 * Overview: Unit test for the fullDeckCount function in dominion.c
 *
 * Input: None
 * Output: Prints to stdout the PASS/FAIL status for each test along with 
 *          a diagnostic hint
 * 
 *  Based on the testUpdateCoins.c code template provided as part of OSU CS362
 *  
 *  Build this test with:
 *      make test2
 ******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "unitTestCommon.h"
#include <string.h>
#include <stdio.h>

int main() {
    int handCards, deckCards, discardCards, player, card, expect, result;
    int failCount = 0;
    char* param1 = "hand count of card number";
    char* param2 = "deck count of card number";
    char* param3 = "discard count of card number";
    char* param4 = "hand count";
    char* param5 = "deck count";
    char* param6 = "discard count";
    char* param;
    struct gameState G;

    printf ("TESTING fullDeckCount():\n\n");
    
    //Run the test for each card type and for each of 2 players
    for(player = 0; player < 2; player++) {
        //Test for each possible card
        for(card = curse; card <= treasure_map; card++) {
            memset(&G, 23, sizeof(struct gameState));   // clear the game state
            G.handCount[player] = 0;
            //Add target card to the player's hand
            for(handCards = 0; handCards < 6; handCards++) {
                //Clear deckCards and discardCards before each run
                for(deckCards = 0; deckCards < 6; deckCards++) {
                    G.deck[player][deckCards] = -1;
                    for(discardCards = 0; discardCards < 6; discardCards++) {
                        G.discard[player][discardCards] = -1;
                    }
                }
                deckCards = 0;
                discardCards = 0;
                G.deckCount[player] = 0;
                G.discardCount[player] = 0;
                expect = handCards + deckCards + discardCards;
                //Test the constructed deck against fullDeckCount()
                result = fullDeckCount(player, card, &G);
                result = myCompare(expect, result);
                if(result != 0) failCount++;
                param = param1;
                printResult(result, param, card);        
                
                //Add target card to the player's deck
                for(deckCards = 0; deckCards < 6; deckCards++) {
                    //Clear discardCards before each run
                    for(discardCards = 0; discardCards < 6; discardCards++) {
                        G.discard[player][discardCards] = -1;
                    }
                    G.discardCount[player] = 0;
                    discardCards = 0;
                    
                    expect = handCards + deckCards + discardCards;
                    //Test the constructed deck against fullDeckCount()
                    result = fullDeckCount(player, card, &G);
                    result = myCompare(expect, result);
                    if(result != 0) failCount++;
                    param = param2;
                    printResult(result, param, card);
                    
                    //Add target card to the player's discard pile
                    for(discardCards = 0; discardCards < 6; discardCards++) {
                        expect = handCards + deckCards + discardCards;
                        //Test the constructed deck against fullDeckCount()
                        result = fullDeckCount(player, card, &G);
                        result = myCompare(expect, result);
                        if(result != 0) failCount++;
                        param = param3;
                        printResult(result, param, card);
                        
                        //Add the card to the player's discard pile
                        G.discard[player][discardCards] = card;
                        G.discardCount[player]++;
                    }
                    //Add the card to the player's deck
                    G.deck[player][deckCards] = card;
                    G.deckCount[player]++;
                }
                //Add the card to the player's hand
                G.hand[player][handCards] = card;
                G.handCount[player]++;
            } 
        }
    }
    
    printSummary(failCount);

    return 0;
}