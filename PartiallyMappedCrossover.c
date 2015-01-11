/* 
 * File:   PartiallyMappedCrossover.c
 * Author: bamasyali
 *
 * Created on October 27, 2013, 15:27 PM
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

#ifndef PMC_H
#define PMC_H 1
#include "PartiallyMappedCrossover.h"
#endif

Chromosome * crossover(Chromosome * c1, Chromosome * c2, int s1, int s2) {
    int cityNumber = c1->cityNumber;

    Chromosome * newChromosome = initChromosome(cityNumber);

    int i;
    for (i = 0; i < cityNumber; i++) {
        newChromosome->values[i] = -1;
    }

    for (i = s1; i < s2; i++) {
        newChromosome->values[i] = c1->values[i];
    }

    for (i = s1; i < s2; i++) {
        int temp = c2->values[i];

        int j;
        int exists = 0;
        for (j = s1; j < s2; j++) {
            if (temp == newChromosome->values[j]) {
                exists = 1;
                break;
            }
        }

        if (exists == 1) {
            continue;
        }

        exists = 0;

        int valueAtTempsPlaceInNewChromosome = newChromosome->values[i];

label:

        for (j = 0; j < cityNumber; j++) {
            if (c2->values[j] == valueAtTempsPlaceInNewChromosome) {
                if (j < s1 || j > s2 - 1) {
                    newChromosome->values[j] = temp;
                } else {
                    exists = 1;
                    valueAtTempsPlaceInNewChromosome = c1->values[j];
                    goto label;
                }
                break;
            }
        }
    }

    for (i = 0; i < cityNumber; i++) {
        if (newChromosome->values[i] == -1) {
            newChromosome->values[i] = c2->values[i];
        }
    }

    return newChromosome;
}

Chromosome ** performPartiallyMappedCrossover(Chromosome * c1, Chromosome * c2, int cityNumber) {

    int s1 = rand() % cityNumber;
    //printf("%d", s1);
    int s2 = s1 + rand() % (cityNumber - s1);
    //printf(" %d\n", s2);


    Chromosome * child1 = crossover(c1, c2, s1, s2);
    Chromosome * child2 = crossover(c2, c1, s1, s2);

    Chromosome ** result = (Chromosome**) malloc(2 * sizeof (Chromosome*));

    result[0] = child1;
    result[1] = child2;

    return result;
}

