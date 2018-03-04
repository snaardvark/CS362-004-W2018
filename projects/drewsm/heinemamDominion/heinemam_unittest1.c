/* -------------------------------------------------------------------------
 * Unit test for function discardCard()
 * -------------------------------------------------------------------------
 */
//NOTE - Fix code to get 100% coverage

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#include <stdio.h>
#include <string.h>

int main() {
	struct gameState G;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	             sea_hag, tribute, smithy
	            };

	int handCount;
	int player = 0;
	int playedCardCount;

	printf("Starting discardCard() test...\n");

	memset(&G, 23, sizeof(struct gameState));
	initializeGame(2, k, 1000, &G);

	printf("\nTesting with card at last position in hand:\n");
	handCount = 5;
	playedCardCount = 0;
	G.handCount[player] = handCount;
	G.playedCardCount = 0;
	discardCard(4, player, &G, 0);
	handCount--;
	playedCardCount++;

	if(handCount == G.handCount[player] && playedCardCount == G.playedCardCount){
		printf("PASSED\n");
		printf("discardCard(): Expected Hand Count: %d; Actual Hand Count: %d\n", handCount, G.handCount[player]);
		printf("discardCard(): Expected Played Card Count: %d; Actual Played Card Count: %d\n", playedCardCount, G.playedCardCount);
	}
	else{
		printf("FAILED\n");
		printf("discardCard(): Expected Hand Count: %d; Actual Hand Count: %d\n", handCount, G.handCount[player]);
		printf("discardCard(): Expected Played Card Count: %d; Actual Played Card Count: %d\n", playedCardCount, G.playedCardCount);
	}

	printf("\nTesting with 1 card left in hand:\n");
	handCount = 1;
	playedCardCount = 0;
	G.handCount[player] = handCount;
	G.playedCardCount = 0;
	discardCard(0, player, &G, 0);
	handCount--;
	playedCardCount++;

	if(handCount == G.handCount[player] && playedCardCount == G.playedCardCount){
		printf("PASSED\n");
		printf("discardCard(): Expected Hand Count: %d; Actual Hand Count: %d\n", handCount, G.handCount[player]);
		printf("discardCard(): Expected Played Card Count: %d; Actual Played Card Count: %d\n", playedCardCount, G.playedCardCount);
	}
	else{
		printf("FAILED\n");
		printf("discardCard(): Expected Hand Count: %d; Actual Hand Count: %d\n", handCount, G.handCount[player]);
		printf("discardCard(): Expected Played Card Count: %d; Actual Played Card Count: %d\n", playedCardCount, G.playedCardCount);
	}

	printf("\nTesting with card in middle position of hand:\n");
	handCount = 5;
	playedCardCount = 0;
	G.handCount[player] = handCount;
	G.playedCardCount = 0;
	discardCard(3, player, &G, 0);
	handCount--;
	playedCardCount++;

	if(handCount == G.handCount[player] && playedCardCount == G.playedCardCount){
		printf("PASSED\n");
		printf("discardCard(): Expected Hand Count: %d; Actual Hand Count: %d\n", handCount, G.handCount[player]);
		printf("discardCard(): Expected Played Card Count: %d; Actual Played Card Count: %d\n", playedCardCount, G.playedCardCount);
	}
	else{
		printf("FAILED\n");
		printf("discardCard(): Expected Hand Count: %d; Actual Hand Count: %d\n", handCount, G.handCount[player]);
		printf("discardCard(): Expected Played Card Count: %d; Actual Played Card Count: %d\n", playedCardCount, G.playedCardCount);
	}

	return 0;
}