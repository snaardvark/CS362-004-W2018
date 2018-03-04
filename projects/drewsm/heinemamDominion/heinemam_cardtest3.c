/* -----------------------------------------------------------
 * Unit test for sea_hag
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

	initializeGame(4, k, 1000, &G);
	int i;
	int expectedDeckCount;

	expectedDeckCount = G.deckCount[1];

	cardEffect(sea_hag, -1, -1, -1, &G, -1, 0);

	printf("%d\n", G.deckCount[1]);
	for (i = 1; i < 4; i++) {
		if (G.deck[i][G.deckCount[i] - 1] == curse && G.deckCount[i] == expectedDeckCount) {
			printf("PASSED all tests\n");
		}
		else {
			printf("FAILED expected deckCount %d; Actual deck count %d\n", expectedDeckCount, G.deckCount[i]);
			if (G.deck[i][G.deckCount[i] - 1] != curse) {
				printf("FAILED top card not curse\n");
			}
		}
	}


	return 0;
}