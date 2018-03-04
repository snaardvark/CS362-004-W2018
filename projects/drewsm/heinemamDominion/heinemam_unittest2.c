/* -----------------------------------------------------------
 * Unit Test for function gainCard()
 * -----------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	struct gameState G;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	             sea_hag, tribute, smithy
	            };

	initializeGame(2, k, 1000, &G);
	
	int c;
	int toFlag;
	int discardCount = G.discardCount[0];
	int deckCount = G.deckCount[0];
	int handCount = G.handCount[0];
	int failedCount = 0;
	int supply;
	int supplyCount;

	printf("Testing function gainCard():\n");
	printf("\nCount Values before test:\n");
	printf("     discardCount: %d\n"
		"     deckCount: %d\n"
		"     handCount: %d\n", G.discardCount[0], G.deckCount[0], G.handCount[0]);


	for(c = curse; c <= treasure_map; c++){
		supplyCount = G.supplyCount[c];
		for(toFlag = 0; toFlag < 3; toFlag++){
			
			supply = gainCard(c, &G, toFlag, 0);
			
			if(supply == -1)
				break;

			supplyCount--;
			if(toFlag == 0){
				discardCount++;

				if(discardCount != G.discardCount[0]){
					printf("gainCard(): FAILED Expected discardCount %d Actual discardCount %d\n", discardCount, G.discardCount[0]);
					failedCount++;
				}
			}
			else if(toFlag == 1){
				deckCount++;

				if(deckCount != G.deckCount[0]){
					printf("gainCard(): FAILED Expected deckCount %d Actual deckCount %d\n", deckCount, G.deckCount[0]);
					failedCount++;
				}
			}
			else{
				handCount++;

				if(handCount != G.handCount[0]){
					printf("gainCard(): FAILED Expected handCount %d Actual handCount %d\n", handCount, G.handCount[0]);
					failedCount++;
				}
			}
		}
		if(supplyCount != G.supplyCount[c]){
			printf("gainCard(): FAILED Expected supplyCount %d Actual supplyCount %d\n", supplyCount, G.supplyCount[c]);
			failedCount++;
		}
	}
	if(failedCount > 0){
		printf("%d tests FAILED\n", failedCount);
	}
	else{
		printf("PASSED all tests\n");
	}

	return 0;
}