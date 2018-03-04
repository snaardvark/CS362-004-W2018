/* ---------------------------------------------------------------
 * Random tester for adventurer card
 * --------------------------------------------------------------*/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <time.h>


void checkAdventureCard(int p, struct gameState *post, int deckTreasure, int failedCount);

int main() {
	srand(time(0));
	int i, j, p, temp;
	int emptyDeck, deckCount, discardCount;
	int failedCount = 0;

	int deckTreasure;
	int discardTreasure;

	struct gameState G;

	printf("Testing adventurer.\n");
	printf("Random Tests\n");

	SelectStream(2);
	PutSeed(3);

	for (i = 0; i < 500; i++) {
		for (j = 0; j < sizeof(struct gameState); j++) {
			((char*)&G)[j] = floor(Random() * 256);
		}
		p = floor(Random() * 4);
		G.whoseTurn = p;

		
		G.deckCount[p] = floor(Random() * (MAX_DECK / 2));
		G.handCount[p] = floor(Random() * MAX_HAND);
		G.discardCount[p] = floor(Random() * (MAX_DECK / 2));
		
		deckTreasure = 0;
		discardTreasure = 0;

		emptyDeck = rand() % 2;

		deckCount = G.deckCount[p];
		discardCount = G.discardCount[p];


		if (emptyDeck == 0 && deckCount >= 2) {

			for (j = 0; j < deckCount; j++) {
				G.deck[p][j] = rand() % 27;
		
				if (G.deck[p][j] == copper || G.deck[p][j] == silver || G.deck[p][j] == gold) {
					deckTreasure++;
				}
			}
			if (deckTreasure < 2) {
				do {
					j = rand() % deckCount;

					temp = G.deck[p][j];
					if (temp != copper && temp != silver && temp != gold) {
						G.deck[p][j] = copper;
						deckTreasure++;
					}
		
				} while (deckTreasure < 2);
			}
			for (j = 0; j < discardCount; j++) {
				G.discard[p][j] = rand() % 27;
		
				if (G.discard[p][j] == copper || G.discard[p][j] == silver || G.discard[p][j] == gold) {
					discardTreasure++;
				}
			}
		}
		else {
			for (j = 0; j < deckCount; j++) {
				G.deck[p][j] = rand() % 27;
		
				if (G.deck[p][j] == copper || G.deck[p][j] == silver || G.deck[p][j] == gold) {
					deckTreasure++;
				}
			}
			for (j = 0; j < discardCount; j++) {
				G.discard[p][j] = rand() % 27;
		
				if (G.discard[p][j] == copper || G.discard[p][j] == silver || G.discard[p][j] == gold) {
					discardTreasure++;
				}
			}
			if (deckTreasure + discardTreasure < 2) {
				do {
					if (discardTreasure < (2 - deckTreasure + discardTreasure)) {
						G.discardCount[p]++;
						discardCount = G.discardCount[p];
						G.discard[p][discardCount - 1] = copper;
						discardTreasure++;
					}
		
				} while (deckTreasure + discardTreasure < 2);
			}
		}

		checkAdventureCard(p, &G, deckTreasure, failedCount);
	}
	if(failedCount == 0)
		printf("All tests passed!\n");
	else
		printf("%d tests failed\n", failedCount);

	return 0;
}

void checkAdventureCard(int p, struct gameState *post, int deckTreasure, int failedCount) {
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	
	int i;
	int preTreasureCount = 0;
	int postTreasureCount = 0;

	adventurerCard(post, p);

	if (deckTreasure < 2) {
		memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
		memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);
	

		if (post->handCount[p] != pre.handCount[p] + 2) {
			printf("Expected handCount %d, Actual handCount %d\n", pre.handCount[p] + 2, post->handCount[p]);
			failedCount++;
		}

		for (i = 0; i < pre.handCount[p]; i++) {
			if (pre.hand[p][i] == copper || pre.hand[p][i] == silver || pre.hand[p][i] == gold)
				preTreasureCount++;
		}

		for (i = 0; i < post->handCount[p]; i++) {
			if (post->hand[p][i] == copper || post->hand[p][i] == silver || post->hand[p][i] == gold)
				postTreasureCount++;
		}

		if (postTreasureCount != preTreasureCount + 2) {
			printf("Expected treasure count %d, Actual treasure count %d\n", preTreasureCount + 2, postTreasureCount);
			failedCount++;
		}

		if (pre.deckCount[p] + pre.discardCount[p] - 2 != post->deckCount[p] + post->discardCount[p]) {
			printf("Expected count on deck and discard %d, Acutal count on deck and discard %d\n", pre.deckCount[p] + pre.discardCount[p] - 2, post->deckCount[p] + post->discardCount[p]);
			failedCount++;
		}
	}
	else {
		if (post->handCount[p] != pre.handCount[p] + 2) {
			printf("Expected handCount %d, Actual handCount %d\n", pre.handCount[p] + 2, post->handCount[p]);
			failedCount++;
		}
		for (i = 0; i < pre.handCount[p]; i++) {
			if (pre.hand[p][i] == copper || pre.hand[p][i] == silver || pre.hand[p][i] == gold)
				preTreasureCount++;
		}

		for (i = 0; i < post->handCount[p]; i++) {
			if (post->hand[p][i] == copper || post->hand[p][i] == silver || post->hand[p][i] == gold)
				postTreasureCount++;
		}

		if (postTreasureCount != preTreasureCount + 2) {
			printf("Expected treasure count %d, Actual treasure count %d\n", preTreasureCount + 2, postTreasureCount);
			failedCount++;
		}

		if (pre.deckCount[p] + pre.discardCount[p] - 2 != post->deckCount[p] + post->discardCount[p]) {
			printf("Expected count on deck and discard %d, Acutal count on deck and discard %d\n", pre.deckCount[p] + pre.discardCount[p] - 2, post->deckCount[p] + post->discardCount[p]);
			failedCount++;
		}
	}

}