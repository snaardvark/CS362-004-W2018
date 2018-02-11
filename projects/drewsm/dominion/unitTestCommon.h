/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   unitTestCommon.h
 * Author: mel
 *
 * Created on January 31, 2018, 8:20 PM
 */

#ifndef UNITTESTCOMMON_H
#define UNITTESTCOMMON_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#include <string.h>
#include <stdio.h>
#include "interface.h"

//Specify the number of rounds for random tests
#define ROUNDS 100

int myCompare(int, int);
void printResult(int, char*, int);
void printSummary(int);

//Global variable
//char* cardNames[treasure_map + 1] = {"curse", "estate", "duchy", "province"
//        , "copper", "silver", "gold", "adventurer", "council_room", "feast"
//        , "gardens", "mine", "remodel", "smithy", "village", "baron"
//        , "great_hall", "minion", "steward", "tribute", "ambassador", "cutpurse"
//        , "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};

#endif /* UNITTESTCOMMON_H */

