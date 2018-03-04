/* --------------------------------------------------------------
 * random test for steward
 * --------------------------------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

void testSteward(int p, struct gameState *post, int choice1, int choice2, int choice3, int failedCount);

int main(){
	srand(time(0));
	struct gameState G;
	int i, j, p, choice1, choice2, choice3;
	int failedCount = 0;

	int k[27] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	             sea_hag, tribute, smithy, curse, estate, duchy, province, copper,
	             silver, gold, council_room, feast, remodel, baron, great_hall,
	             steward, ambassador, outpost, salvager, treasure_map
	            };

	SelectStream(2);
	PutSeed(3);

	printf("Testing Steward.\n");
	printf("Random Tests\n");

	for(i = 0; i < 1000; i++){
		for (j = 0; j < sizeof(struct gameState); j++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		p = rand() % MAX_PLAYERS;
		G.whoseTurn = p;
		G.deckCount[p] = rand() % MAX_DECK;
		G.discardCount[p] = rand() % MAX_DECK;
		G.handCount[p] = rand() % MAX_HAND + 3;
		G.playedCardCount = 0;
		G.coins = 0;

		G.hand[p][0] = steward;

		for(j = 1; j < G.handCount[p]; j++){
			G.hand[p][j] = k[rand() % 27];
		}

		for(j = 0; j < G.deckCount[p]; j++){
			G.deck[p][j] = k[rand() % 27];
		}

		for(j = 0; j < G.discardCount[p]; j++){
			G.discard[p][j] = k[rand() % 27];
		}

		choice1 = rand() % 3;
		choice2 = rand() % G.handCount[p] + 1;
		choice3 = rand() % G.handCount[p] + 1;

		while(choice3 == choice2)
			choice3 = rand() % G.handCount[p] + 1;

		testSteward(p, &G, choice1, choice2, choice3, failedCount);
	}

	if(failedCount == 0)
		printf("All tests passed!\n");
	else
		printf("%d tests failed\n", failedCount);

	return 0;
}

void testSteward(int p, struct gameState *post, int choice1, int choice2, int choice3, int failedCount){
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));



	cardEffect(steward, choice1, choice2, choice3, post, 0, 0);


	if(choice1 == 1){
		if(post->handCount[p] != pre.handCount[p] + 1){
			printf("FAILED: Expected handCount %d, Actual handCount %d\n", pre.handCount[p] + 1, post->handCount[p]);
			failedCount++;
		}
		if(post->coins != pre.coins){
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins, post->coins);	
			failedCount++;	
		}
	}
	else if(choice1 == 2){
		if(post->handCount[p] != pre.handCount[p] - 1){
			printf("FAILED: Expected handCount %d, Actual handCount %d\n", pre.handCount[p] - 1, post->handCount[p]);
			failedCount++;
		}
		if(post->coins != pre.coins + 2){
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins + 2, post->coins);	
			failedCount++;	
		}
	}
	else{
		if(post->handCount[p] != pre.handCount[p] - 3){
			printf("FAILED: Expected handCount %d, Actual handCount %d\n", pre.handCount[p] - 3, post->handCount[p]);
			failedCount++;
		}
		if(post->coins != pre.coins){
			printf("FAILED: Expected coins %d, Actual coins %d\n", pre.coins, post->coins);	
			failedCount++;	
		}
	}
}