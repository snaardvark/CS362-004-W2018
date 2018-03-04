/* -----------------------------------------------------------
 * Unit test for fullDeckCount()
 * -----------------------------------------------------------*/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#include <stdio.h>

int main() {
	struct gameState G;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	             sea_hag, tribute, smithy
	            };

	initializeGame(2, k, 1000, &G);

	int i;
	int cardCount = 0;
	int curDeckCount = G.deckCount[0];
	int curHandCount = G.handCount[0];
	int curDiscardCount = G.discardCount[0];
	int testCount;

	printf("Testing fullDeckCount():\n");

	//set deck with specific cards
	for (i = curDeckCount; i < curDeckCount + 2; i++) {
		G.deck[0][i] = curse;
		G.deckCount[0]++;
		cardCount++;
	}
	for (i = curHandCount; i < curHandCount + 1; i++) {
		G.hand[0][i] = curse;
		G.handCount[0]++;
		cardCount++;
	}
	for (i = curDiscardCount; i < curDiscardCount + 3; i++) {
		G.discard[0][i] = curse;
		G.discardCount[0]++;
		cardCount++;
	}

	testCount = fullDeckCount(0, curse, &G);

	if (cardCount != testCount) {
		printf("FAILED Expected %d Actual %d\n", cardCount, testCount);
	}
	else
		printf("PASS Expected %d Actual %d\n", cardCount, testCount);


	return 0;
}