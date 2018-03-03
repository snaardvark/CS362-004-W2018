/* -----------------------------------------------------------
 * Unit test for smithyCard()
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
	int expectedHandCount;
	int failedCount = 0;

	//insert smithy card
	G.hand[0][3] = smithy;

	expectedHandCount = G.handCount[0] + 2;

	printf("hand count before call: %d\n", G.handCount[0]);

	cardEffect(smithy, -1, -1, -1, &G, 3, 0);

	if (G.handCount[0] != expectedHandCount) {
		printf("FAILED Expected hand count: %d; Actual hand count: %d\n", expectedHandCount, G.handCount[0]);
		failedCount++;
	}

	for(i = 0; i < G.handCount[0]; i++){
		if(G.hand[0][i] == smithy){
			printf("FAILED to discard smithy\n");
			failedCount++;
		}
	}

	return 0;
}
