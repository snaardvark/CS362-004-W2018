/* -----------------------------------------------------
 * Unit test for adventurerCard()
 * -----------------------------------------------------*/
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
	int checkDeckCount;
	int checkHandCount;
	int checkDiscardCount;
	int failedCount = 0;



	//set hand
	for (i = 0; i < 5; i++)
		G.hand[0][i] = k[i];

	//set deck
	G.deck[0][0] = gold;
	G.deck[0][1] = gardens;
	G.deck[0][2] = embargo;
	G.deck[0][3] = estate;
	G.deck[0][4] = silver;
	G.deck[0][5] = copper;
	G.deckCount[0]++;

	printf("Starting deck count: %d\n", G.deckCount[0]);
	printf("\nDeck contents before function call:\n");
	for (i = 0; i < G.deckCount[0]; i++) {
		if (G.deck[0][i] == estate)
			printf("estate\n");
		else if (G.deck[0][i] == gardens)
			printf("gardens\n");
		else if (G.deck[0][i] == gold)
			printf("gold\n");
		else if (G.deck[0][i] == embargo)
			printf("embargo\n");
		else if (G.deck[0][i] == silver)
			printf("silver\n");
		else if (G.deck[0][i] == copper)
			printf("copper\n");
	}
	checkDeckCount = G.deckCount[0] - 2;

	printf("\nStarting hand count: %d\n", G.handCount[0]);
	printf("\nHand contents before function call:\n");
	for (i = 0; i < G.handCount[0]; i++) {
		if (G.hand[0][i] == adventurer)
			printf("adventurer\n");
		else if (G.hand[0][i] == gardens)
			printf("gardens\n");
		else if (G.hand[0][i] == embargo)
			printf("embargo\n");
		else if (G.hand[0][i] == village)
			printf("village\n");
		else if (G.hand[0][i] == minion)
			printf("minion\n");
	}
	checkHandCount = G.handCount[0] + 2;

	printf("\nStarting discard count: %d\n", G.discardCount[0]);

	checkDiscardCount = G.discardCount[0];

	printf("\n-----------------------------------------------------\n");
	printf("\nTesting Adventurer...\n");
	cardEffect(adventurer, -1, -1, -1, &G, -1, 0);
	printf("\n-----------------------------------------------------\n");

	if (G.deckCount[0] !=  checkDeckCount) {
		printf("\nFAILED New deck count: %d; Expected: %d\n", G.deckCount[0], checkDeckCount);
		failedCount++;

		printf("\nDeck contents after function call:\n");
		for (i = 0; i < G.deckCount[0]; i++) {
			if (G.deck[0][i] == estate)
				printf("estate\n");
			else if (G.deck[0][i] == gardens)
				printf("gardens\n");
			else if (G.deck[0][i] == gold)
				printf("gold\n");
			else if (G.deck[0][i] == embargo)
				printf("embargo\n");
			else if (G.deck[0][i] == silver)
				printf("silver\n");
			else if (G.deck[0][i] == copper)
				printf("copper\n");
		}

		printf("\nExpected deck contents:\n");
		printf("estate\n");
		printf("gardens\n");
		printf("gold\n");
		printf("embargo\n");

		printf("\n-------------------------------------------------\n");
	}

	if (G.handCount[0] != checkHandCount) {
		printf("\nFAILED New handcount: %d; Expected %d\n", G.handCount[0], checkHandCount);
		failedCount++;

		printf("\nHand Contents after function call:\n");

		for (i = 0; i < G.handCount[0]; i++) {
			if (G.hand[0][i] == adventurer)
				printf("adventurer\n");
			else if (G.hand[0][i] == gardens)
				printf("gardens\n");
			else if (G.hand[0][i] == embargo)
				printf("embargo\n");
			else if (G.hand[0][i] == village)
				printf("village\n");
			else if (G.hand[0][i] == minion)
				printf("minion\n");
			else if (G.hand[0][i] == gold)
				printf("gold\n");
			else if (G.hand[0][i] == silver)
				printf("silver\n");
			else if (G.hand[0][i] == copper)
				printf("copper\n");
		}

		printf("\nExpected hand contents:\n");
		printf("adventurer\n");
		printf("gardens\n");
		printf("embargo\n");
		printf("village\n");
		printf("minion\n");
		printf("silver\n");
		printf("copper\n");

		printf("\n-----------------------------------------------------\n");
	}

	if (G.discardCount[0] != checkDiscardCount) {
		printf("\nFAILED New discard count: %d; Expected: %d\n", G.discardCount[0], checkDiscardCount);
		failedCount++;

		printf("\nDiscard contents after function call:\n");
		for (i = 0; i < G.discardCount[0]; i++) {
			if (G.discard[0][i] == estate)
				printf("estate\n");
			else if (G.discard[0][i] == gardens)
				printf("gardens\n");
			else if (G.discard[0][i] == embargo)
				printf("embargo\n");
		}

		printf("\nExpected discard contents:\n");
	}

	if(failedCount == 0)
		printf("PASSED all tests\n");

	return 0;
}