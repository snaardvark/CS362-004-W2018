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

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>

//Global variable

//function definitions
int myCompare(int, int);
void printResult(int, char*, int);
void printSummary(int);
void printHeader(char*);

#endif /* UNITTESTCOMMON_H */

