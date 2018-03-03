/* --------------------------------------------------------------
 * random test for salvager
 * --------------------------------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

void testSalvCard(int p, struct gameState *post, int choice, int failedCount);

int main() {
	srand(time(0));

	int k[27] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	             sea_hag, tribute, smithy, curse, estate, duchy, province, copper,
	             silver, gold, council_room, feast, remodel, baron, great_hall,
	             steward, ambassador, outpost, salvager, treasure_map
	            };

	struct gameState G;
	int i, j, p, choice;
	int failedCount = 0;

	SelectStream(2);
	PutSeed(3);

	printf("Testing Salvager.\n");
	printf("Random Tests\n");

	for (i = 0; i < 10000; i++) {
		for (j = 0; j < sizeof(struct gameState); j++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		p = rand() % MAX_PLAYERS;
		G.whoseTurn = p;
		G.handCount[p] = rand() % MAX_HAND + 1;
		G.coins = 0;
		G.playedCardCount = 0;
		G.numBuys = 0;

		for (j = 0; j < G.handCount[p]; j++) {
			G.hand[p][j] = k[rand() % 27];
		}

		G.hand[p][0] = salvager;

		choice = rand() % G.handCount[p] + 1;

		if (choice == G.handCount[p])
			choice--;


		testSalvCard(p, &G, choice, failedCount);
	}
	if (failedCount == 0) {
		printf("All tests passed!\n");
	}
	else {
		printf("%d tests failed\n", failedCount);
	}


	return 0;
}

void testSalvCard(int p, struct gameState *post, int choice, int failedCount) {
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));


	cardEffect(salvager, choice, -1, -1, post, 0, 0);

	//check that buys increased
	if (post->numBuys != pre.numBuys + 1) {
		printf("FAILED: Expected %d buys, Actual %d buys\n", pre.numBuys + 1, post->numBuys);
		failedCount++;
	}

	//check that cards were discarded from hand
	if (pre.handCount[p] == 1) {
		if (post->handCount[p] != pre.handCount[p] - 1) {
			printf("FAILED: Expected handCount %d, Actual handCount %d\n", pre.handCount[p] - 1, post->handCount[p]);
			failedCount++;
		}
	}
	else if (post->handCount[p] != pre.handCount[p] - 2) {
		printf("FAILED: Expected handCount %d, Actual handCount %d\n", pre.handCount[p] - 2, post->handCount[p]);
		failedCount++;
	}

	//check that coins was updated properly
	if (pre.handCount[p] > 1) {
		if (pre.hand[p][choice] == curse && post->coins != pre.coins) {
			printf("curse failed\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == estate && post->coins != pre.coins + 2) {
			printf("estate\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 2, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == duchy && post->coins != pre.coins + 5) {
			printf("duchy\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 5, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == province && post->coins != pre.coins + 8) {
			printf("province\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 8, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == copper && post->coins != pre.coins) {
			printf("copper\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == silver && post->coins != pre.coins + 3) {
			printf("silver\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 3, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == gold && post->coins != pre.coins + 6) {
			printf("gold\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 6, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == adventurer && post->coins != pre.coins + 6) {
			printf("adventurer\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 6, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == council_room && post->coins != pre.coins + 5) {
			printf("council_room\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 5, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == feast && post->coins != pre.coins + 4) {
			printf("feast\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 4, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == gardens && post->coins != pre.coins + 4) {
			printf("gardens\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 4, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == mine && post->coins != pre.coins + 5) {
			printf("mine\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 5, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == remodel && post->coins != pre.coins + 4) {
			printf("remodel\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 4, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == smithy && post->coins != pre.coins + 4) {
			printf("smithy\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 4, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == village && post->coins != pre.coins + 3) {
			printf("village\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 3, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == baron && post->coins != pre.coins + 4) {
			printf("baron\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 4, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == great_hall && post->coins != pre.coins + 3) {
			printf("great_hall\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 3, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == minion && post->coins != pre.coins + 5) {
			printf("minion\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 5, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == steward && post->coins != pre.coins + 3) {
			printf("steward\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 3, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == tribute && post->coins != pre.coins + 5) {
			printf("tribute\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 5, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == ambassador && post->coins != pre.coins + 3) {
			printf("ambassador\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 3, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == cutpurse && post->coins != pre.coins + 4) {
			printf("cutpurse\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 4, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == embargo && post->coins != pre.coins + 2) {
			printf("embargo\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 2, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == outpost && post->coins != pre.coins + 5) {
			printf("outpost\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 5, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == salvager && post->coins != pre.coins + 4) {
			printf("salvager\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 4, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == sea_hag && post->coins != pre.coins + 4) {
			printf("sea_hag\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 4, post->coins);
			failedCount++;
		}
		else if (pre.hand[p][choice] == treasure_map && post->coins != pre.coins + 4) {
			printf("treasure_map\n");
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 4, post->coins);
			failedCount++;
		}
	}
}