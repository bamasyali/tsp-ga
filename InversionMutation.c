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

#ifndef GENETIC_H
#define GENETIC_H 1
#include "Genetic.h"
#endif

#ifndef INVERSION_H
#define INVERSION_H 1
#include "InversionMutation.h"
#endif

void performInversionMutation(Chromosome * chromosome) {

    int rnd1 = rand() % chromosome->cityNumber;
    int rnd2 = (rand() % (chromosome->cityNumber - rnd1)) + rnd1;

    int * tempArray = (int*) malloc((rnd2 - rnd1 + 1) * sizeof (int));
    int temp = rnd2 - rnd1;

    int j;
    for (j = rnd1; j <= rnd2; j++) {
        tempArray[temp] = chromosome->values[j];
        temp--;
    }

    temp = 0;
    for (j = rnd1; j <= rnd2; j++) {
        chromosome->values[j] = tempArray[temp];
        temp++;
    }
    free(tempArray);


}
