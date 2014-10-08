/* 
 * File:   InsertMutation.h
 * Author: bamasyali
 *
 * Created on November 03, 2013, 12:18 PM
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

#ifndef INSERT_H
#define INSERT_H 1
#include "InsertMutation.h"
#endif

void performInsertMutation(Genetic * genetic) {
    int i;
    for (i = 0; i < genetic->chromosomeNumber; i++) {

        int random = rand() % 1000;
        if (random > 5) {
            continue;
        }

        Chromosome * chromosome = genetic->chromosomes + i;

        int rnd1 = rand() % genetic->cityNumber;
        int rnd2 = (rand() % (genetic->cityNumber - rnd1)) + rnd1;

        int j;
        for (j = rnd2; j > rnd1 + 1; j--) {
            int temp = chromosome->values[j];
            chromosome->values[j] = chromosome->values[j - 1];
            chromosome->values[j - 1] = temp;
        }
    }
}
