#include "randTestCommon.h"

//Return a random from 0 - max generated from a randomly selected stream
int getRandom(int max) {
    int z;
    int maxStreams = 255;
    SelectStream(1);
    z = floor(Random() * (maxStreams + 1));
    SelectStream(z);
    z = floor(Random() * (max + 1));
    return z;
}

/* Build a game with randomized values, but make sure the kingdom cards are 
 * included that we need to test
 */
void randGame(struct gameState *game) {
    int kingCards[10];
    kingCards[0] = adventurer;
    kingCards[1] = embargo;
    kingCards[2] = smithy;
    int numSelected = 3;
    int i, used, card;
    int playerNum = 0;
    int randomSeed = -1;
    
    //Replicate some of the functionality of interface.c::selectKingdomCards
    //But stack the deck with some of my refactored cards from Assignment 2
    while(numSelected < 10) {
        used = 0;
        card = getRandom(treasure_map);
        if(card < adventurer) continue; //need to get a different card
        for(i = 0; i < numSelected; i++) {
            if(kingCards[i] == card) {
                used = 1;
                break;
            }
        }
        if(used) continue;  //Only select a kingdom card once
        kingCards[numSelected] = card;
        numSelected++;
    }
    //Set a random number of players in the allowable range of 2 - 4
    do{
        playerNum = getRandom(4);
    }while(playerNum < 2);
    initializeGame(playerNum, kingCards, randomSeed, game);
}

//Set the current game player turn to a random player number
void randPlayer(struct gameState *game) {
    int currentPlayer = getRandom(game->numPlayers - 1);
    while(currentPlayer != game->whoseTurn) {
        endTurn(game);
    }
}

//Randomize the cards in currentPlayer deck, using cards that are in play
void randomizeCards(struct gameState *game, int currentPlayer) {
    int i, cardNum;
    //First empty the deck & put cards back in supply
    for(i = game->deckCount[currentPlayer] - 1; i >= 0; i--) {
        cardNum = game->deck[currentPlayer][i];
        game->deck[currentPlayer][i] = -1;
        game->supplyCount[cardNum]++;
    }
    
    //Draw a random deck of random size up to 10
    game->deckCount[currentPlayer] = getRandom(10);

    for(i = 0; i < game->deckCount[currentPlayer]; i++) {
        //Select a card number that is in the supply
        game->deck[currentPlayer][i] = randSupply(game);
    }
    //Return any cards from the discard pile back to supply
    for(i = game->discardCount[currentPlayer] - 1; i >= 0; i--) {
        cardNum = game->discard[currentPlayer][i];
        game->discard[currentPlayer][i] = -1;
        game->supplyCount[cardNum]++;
    }
    //Put random cards in the discard pile from supply such that currentPlayer
    //deckCount + discardCount = 10
    game->discardCount[currentPlayer] = 10 - game->deckCount[currentPlayer];
    for(i = 0; i < game->discardCount[currentPlayer] - 1; i++) {
        //Select a card number that is in the supply
        do {
            cardNum = getRandom(treasure_map);
        }while(game->supplyCount[cardNum] < 1);
        game->discard[currentPlayer][i] = cardNum;
    }
}

//Supply a random card number that is in the supply
int randSupply(struct gameState *game) {
    int cardNum;
    do {
        cardNum = getRandom(treasure_map);
    }while(game->supplyCount[cardNum] < 1);
    return cardNum;
}

//This function may optionally be called for additional debugging info
void printVars(struct gameState *game) {
    int i, j, cop, est;
    printf("Players = %i\n", game->numPlayers);
//    printf("Curse = %i\n", game->supplyCount[curse]);
//    printf("Estate = %i\n", game->supplyCount[estate]);
//    printf("Duchy = %i\n", game->supplyCount[duchy]);
//    printf("Province = %i\n", game->supplyCount[province]);
    printf("Copper = %i\n", game->supplyCount[copper]);
    printf("Silver = %i\n", game->supplyCount[silver]);
    printf("Gold = %i\n", game->supplyCount[gold]);
    printf("currentPlayer = %i\n", game->whoseTurn);
//    for(i = adventurer; i < treasure_map; i++) {
//        if(game->supplyCount[i] <= 0) continue;
//        printf("Card %i has Qty = %i\n", i, game->supplyCount[i]);
//    }
    for(i = 0; i < game->numPlayers; i++) {
        printf("\nPlayer %i deckCount = %i\n", i, game->deckCount[i]);
        printf("Player %i discardCount = %i\n", i, game->discardCount[i]);
        cop = 0;
        est = 0;
        for(j = 0; j < 10; j++) {
            if(game->deck[i][j] == copper) {
                cop++;
            } else if (game->deck[i][j] == estate) {
                est++;
            }
        }
        printf("Player %i deck has %i coppers and %i estates\n", i, cop, est);
        printf("Player %i handCount = %i\n\n", i, game->handCount[i]);
    }
}

/* int place represents deck (0) || discard(1) || hand (2)
 * Count treasure cards available for currentPlayer
 */
int treasureCount(struct gameState *game, int currentPlayer, int place) {
    int j;
    int treasures = -1;
    if(place == 0) {
        treasures = 0;
        for(j = 0; j < game->deckCount[currentPlayer]; j++) {
            if((game->deck[currentPlayer][j] == copper) ||
                    (game->deck[currentPlayer][j] == silver) ||
                    (game->deck[currentPlayer][j] == gold)) {
                treasures++;
            }
        }
    } else if(place == 1) {
        treasures = 0;
        for(j = 0; j < game->discardCount[currentPlayer]; j++) {
            if((game->discard[currentPlayer][j] == copper) ||
                    (game->discard[currentPlayer][j] == silver) ||
                    (game->discard[currentPlayer][j] == gold)) {
                treasures++;
            }
        }
    } else if(place == 2) {
        treasures = 0;
        for(j = 0; j < game->handCount[currentPlayer]; j++) {
            if((game->hand[currentPlayer][j] == copper) ||
                    (game->hand[currentPlayer][j] == silver) ||
                    (game->hand[currentPlayer][j]) == gold) {
                treasures++;
            }
        }
    }
    return treasures;
}

//Set the value pointed by treasure pointers to a given treasure card
void setTreasure(int *treasure1, int *treasure2, int treasure) {
    int t1 = *treasure1;
    int t2 = *treasure2;
    if(t1 < 0) {
        *treasure1 = treasure;
    } else if (t2 < 0) {
        *treasure2 = treasure;
    }
    return;
}

//Returns highest index of card in currentPlayer hand, if exists, otherwise -1
int findHandPos(struct gameState *game, int card, int currentPlayer) {
    int i;
    int handPos = -1;
    for(i = 0; i < game->handCount[currentPlayer]; i++) {
        if(game->hand[currentPlayer][i] == card) {
            handPos = i;
        }
    }
    return handPos;
}

//Compare function
int myCompare(int val1, int val2) {
    if(val1 < val2)
        return -1;
    else if(val1 > val2)
        return 1;
    else
        return 0;
}

//Print diagnostic results PASS | FAIL | explanation
void printResult(int result, char* param, int value) {
    char *msg;
    char* pass = "PASS: ";
    char* fail = "FAIL: ";
    char* explain = "\texpected value was";
    if(result == 2)
        msg = explain;
    else if(result == 0)
        msg = pass;
    else
        msg = fail;
    if(DEBUG || (result != 0)) {
        printf("%s %s = %i\n", msg, param, value);
    }
}

void printSummary(int failures) {
    printf("\n%i FAILURES FOUND\n", failures);
    if(failures > 0) {
        printf("examine detailed results.\n");
    }
}