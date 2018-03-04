/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   randTestCommon.h
 * Author: mel
 *
 * Created on February 11, 2018, 6:08 PM
 */

#ifndef RANDTESTCOMMON_H
#define RANDTESTCOMMON_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#include <string.h>
#include <stdio.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"

int getRandom(int);
void randGame(struct gameState *);
void randPlayer(struct gameState *);
void randomizeCards(struct gameState *, int);
int randSupply(struct gameState *);
void printVars(struct gameState *);
int treasureCount(struct gameState *, int, int);
void setTreasure(int *, int *, int);
int findHandPos(struct gameState *, int, int);
int myCompare(int, int);
void printResult(int, char*, int);
void printSummary(int);
void printHeader(char*);

#endif /* RANDTESTCOMMON_H */

