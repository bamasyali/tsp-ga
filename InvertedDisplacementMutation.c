/* 
 * File:   InversionMutation.h
 * Author: bamasyali
 *
 * Created on November 11, 2013, 9:18 AM
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

#ifndef DISPLACEMENT_H
#define DISPLACEMENT 1
#include "InvertedDisplacementMutation.h"
#endif

void performInvertedDisplacementMutation(Chromosome * chromosome) {

    int rnd1 = rand() % chromosome->cityNumber;
    int rnd2 = (rand() % (chromosome->cityNumber - rnd1)) + rnd1;
    int rnd3 = rand() % chromosome->cityNumber;

    if (rnd1 == 0 && rnd2 >= chromosome->cityNumber - 1) {
        rnd1++;
        rnd2--;
    }

    while (rnd3 >= rnd1 && rnd2 >= rnd3) {
        rnd3 = rand() % chromosome->cityNumber;
    }

    int * tempArray = (int*) malloc((rnd2 - rnd1 + 1) * sizeof (int));
    int temp = rnd2 - rnd1;

    int j;
    for (j = rnd1; j <= rnd2; j++) {
        tempArray[temp] = chromosome->values[j];
        temp--;
    }

    temp = rnd2 - rnd1;
    if (rnd3 < rnd1) {
        for (j = rnd1 - 1; j >= rnd3; j--) {
            chromosome->values[j + temp + 1] = chromosome->values[j];
        }
        int temp2 = 0;
        for (j = rnd3; j <= rnd3 + temp; j++) {
            chromosome->values[j] = tempArray[temp2++];
        }

    } else if (rnd3 > rnd2) {
        for (j = rnd2 + 1; j <= rnd3; j++) {
            chromosome->values[j - temp] = chromosome->values[j ];
        }
        int temp2 = 0;
        for (j = rnd3 + 1 - temp; j <= rnd3; j++) {
            chromosome->values[j] = tempArray[temp2++];
        }
    } else {
        exit(EXIT_FAILURE);
    }

    free(tempArray);

    for (j = 0; j < chromosome->cityNumber; j++) {
        for (int k = j + 1; k < chromosome->cityNumber; k++) {
            if (chromosome->values[j] == chromosome->values[k]) {
                printf("Error %d %d %d\n\n", j, k, chromosome->values[j]);
                getchar();


            }
        }
    }


}