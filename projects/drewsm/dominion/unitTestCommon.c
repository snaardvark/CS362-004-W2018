/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "unitTestCommon.h"

//Compare function
int myCompare(int val1, int val2) {
    if(val1 < val2)
        return -1;
    else if(val1 > val2)
        return 1;
    else
        return 0;
}


//Define a function here to print the result
void printResult(int result, char* param, int value) {
    char *msg;
    char* pass = "PASS: ";
    char* fail = "FAIL: ";
    char* explain = "\tfailure occurred";
    if(result == -1)
        msg = explain;
    else if(result == 0)
        msg = pass;
    else
        msg = fail;
    printf("%s with %s = %i\n", msg, param, value);
}

void printSummary(int failures) {
    printf("\n%i FAILURES FOUND\n", failures);
    if(failures > 0) {
        printf("examine detailed results.\n");
    }
}