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

void calculateTotalDistance(Chromosome * chromosome, City * cities) {

    double totalDistance = 0;

    int i;
    for (i = 0; i < chromosome->cityNumber - 1; i++) {
        City * c1 = cities + chromosome->values[i];
        City * c2 = cities + chromosome->values[i + 1];
        //printf("%d %d %d\n", i, c1->id, c2->id);
        totalDistance += cities->calculateDistanceById(cities, c1->id, c2->id);
    }

    City * c1 = cities + chromosome->values[chromosome->cityNumber - 1];
    City * c2 = cities + chromosome->values[0];
    totalDistance += cities->calculateDistanceById(cities, c1->id, c2->id);

    chromosome->totalDistance = totalDistance;
}

void validate(Chromosome * chromosome) {
    int i;
    for (i = 0; i < chromosome->cityNumber; i++) {
        int j;
        for (j = i + 1; j < chromosome->cityNumber; j++) {
            if (chromosome->values[i] == chromosome->values[j]) {
                exit(EXIT_FAILURE);
            }
        }
    }
}

void print(Chromosome * chromosome) {
    int i;
    for (i = 0; i < chromosome->cityNumber; i++) {
        printf("%d -> ", chromosome->values[i]);
    }
    printf("\n");
}

void destroy(Chromosome * chromosome) {
    free(chromosome->values);
    free(chromosome);
}

Chromosome * initChromosome(Chromosome * chromosome, int cityNumber) {
    chromosome->values = (int*) malloc(sizeof (int) * cityNumber);
    chromosome->cityNumber = cityNumber;

    chromosome->calculateTotalDistance = &calculateTotalDistance;
    chromosome->destroy = &destroy;

    chromosome->print = &print;
    chromosome->validate = &validate;

    return chromosome;
}

Chromosome * initChromosome(int cityNumber) {
    Chromosome * chromosome = (Chromosome *) malloc(sizeof (Chromosome));

    initChromosome(chromosome, cityNumber);

    return chromosome;
}

Chromosome * readSolutionFromFile(FILE * file, int cityNumber) {

    Chromosome * chromosome = initChromosome(cityNumber);

    int i;
    for (i = 0; i < cityNumber; i++) {
        int id;
        fscanf(file, "%d", &id);
        chromosome->values[i] = id - 1;
    }

    return chromosome;
}