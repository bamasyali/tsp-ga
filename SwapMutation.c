/* 
 * File:   SwapMutation.c
 * Author: bamasyali
 *
 * Created on October 03, 2013, 11:18 AM
 */

#ifndef LIBS
#define LIBS 1
#include <stdio.h>
#include <stdlib.h>
#endif

#ifndef CITY_H
#define CITY_H 1
#include "City.h"
#endif

#ifndef CHROMOSOME_H
#define CHROMOSOME_H 1
#include "Chromosome.h"
#endif

#ifndef SWAP_H
#define SWAP_H 1
#include "SwapMutation.h"
#endif

void performSwapMutation(Chromosome * chromosome) {

    int rnd1 = rand() % chromosome->cityNumber;
    int rnd2 = rand() % chromosome->cityNumber;

    int temp = chromosome->values[rnd1];
    chromosome->values[rnd1] = chromosome->values[rnd2];
    chromosome->values[rnd2] = temp;

}