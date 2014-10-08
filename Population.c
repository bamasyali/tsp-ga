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

void shuffle(int *array, int n) {
    if (n > 1) {
        int i;
        for (i = 0; i < n; i++) {
            int j = rand() % n;
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

void generateChromosome(Chromosome * chromosome) {

    int i;
    for (i = 0; i < chromosome->cityNumber; i++) {
        chromosome->values[i] = i + 1;
    }

    shuffle(chromosome->values, chromosome->cityNumber);
}

void initPopulation(Genetic * genetic) {
    int i;
    int chromosomeSize = genetic->chromosomeNumber;
    for (i = 0; i < chromosomeSize; i++) {
        generateChromosome(genetic->chromosomes + i);
        genetic->chromosomes[i].calculateTotalDistance(genetic->chromosomes + i, genetic->cities);
    }
}
