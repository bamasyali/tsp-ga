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

#ifndef GENETIC_H
#define GENETIC_H 1
#include "Genetic.h"
#endif

#ifndef SWAP_H
#define SWAP_H 1
#include "SwapMutation.h"
#endif

void performSwapMutation(Genetic * genetic) {
    int i;
    for (i = 0; i < genetic->chromosomeNumber; i++) {

        Chromosome * chromosome = genetic->chromosomes + i;

        int rnd1 = rand() % genetic->cityNumber;
        int rnd2 = rand() % genetic->cityNumber;

        int temp = chromosome->values[rnd1];
        chromosome->values[rnd1] = chromosome->values[rnd2];
        chromosome->values[rnd2] = temp;
    }
}