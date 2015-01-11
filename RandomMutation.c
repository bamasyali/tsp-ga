/* 
 * File:   InversionMutation.h
 * Author: bamasyali
 *
 * Created on November 03, 2013, 9:18 PM
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

#ifndef INSERT_H
#define INSERT_H 1
#include "InsertMutation.h"
#endif

#ifndef INVERSION_H
#define INVERSION_H 1
#include "InversionMutation.h"
#endif

#ifndef RANDOM_H
#define RANDOM_H 1
#include "RandomMutation.h"
#endif

void performRandomMutation(Chromosome * chromosome) {
    int random = rand() % 3;
    if (random == 0) {
        performSwapMutation(chromosome);
    } else if (random == 1) {
        performInsertMutation(chromosome);
    } else if (random == 2) {
        performInversionMutation(chromosome);
    }
}
