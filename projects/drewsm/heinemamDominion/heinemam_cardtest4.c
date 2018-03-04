/* -----------------------------------------------------------
 * Unit test for steward
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
	
	int failedCount = 0;
	int expectedHandCount;
	int expectedCoinCount;




	G.hand[0][G.handCount[0] - 1] = steward;
	expectedHandCount = G.handCount[0];


	expectedCoinCount = G.coins;

	expectedHandCount = expectedHandCount + 1;
	cardEffect(steward, 1, -1, -1, &G, (G.handCount[0] - 1), 0);
	if (expectedHandCount != G.handCount[0]) {
		printf("FAILED Expected hand count: %d; Actual hand count: %d\n", expectedHandCount, G.handCount[0]);
		failedCount++;
	}

	G.hand[0][G.handCount[0] - 1] = steward;
	expectedCoinCount = expectedCoinCount + 2;
	cardEffect(steward, 2, -1, -1, &G, (G.handCount[0] - 1), 0);
	if (expectedCoinCount != G.coins) {
		printf("FAILED Expected coin count: %d; Actual coin count: %d\n", expectedCoinCount, G.coins);
		failedCount++;
	}

	G.hand[0][G.handCount[0] - 1] = steward;
	expectedHandCount = G.handCount[0] - 3;
	cardEffect(steward, 3, 1, 2, &G, (G.handCount[0] - 1), 0);
	if (expectedHandCount != G.handCount[0]) {
		printf("FAILED Expected hand count: %d; Actual hand count: %d\n", expectedHandCount, G.handCount[0]);
		failedCount++;
	}

	if (failedCount == 0)
		printf("PASSED all tests\n");

	return 0;
}