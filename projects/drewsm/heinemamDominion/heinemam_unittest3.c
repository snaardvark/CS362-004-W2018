/* -----------------------------------------------------------
 * Unit test for isGameOver()
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

	printf("Testing when province = 0:\n");

	G.supplyCount[province] = 0;

	if(isGameOver(&G) == 1)
		printf("PASS\n");

	printf("Testing when game not over:\n");

	G.supplyCount[province] = 8;

	if(isGameOver(&G) == 0)
		printf("PASS\n");

	printf("Testing when 3 supply piles are empty\n");

	G.supplyCount[curse] = 0;

	G.supplyCount[adventurer] = 0;

	G.supplyCount[smithy] = 0;

	if(isGameOver(&G) == 1)
		printf("PASS\n");

	return 0;
}