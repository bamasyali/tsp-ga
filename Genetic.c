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

#ifndef POPULATION_H
#define POPULATION_H 1
#include "Population.h"
#endif

Genetic * initGenetic(int cityNumber, int generationLimit, int chromosomeNumber, City * cities) {
    Genetic * genetic = (Genetic *) malloc(sizeof (Genetic));

    genetic->cityNumber = cityNumber;
    genetic->generation = 0;
    genetic->generationLimit = generationLimit;
    genetic->chromosomeNumber = chromosomeNumber;
    genetic->chromosomes = (Chromosome *) malloc(sizeof (Chromosome) * chromosomeNumber);
    genetic->cities = cities;

    int i;
    for (i = 0; i < chromosomeNumber; i++) {
        genetic->chromosomes[i].values = (int*) malloc(sizeof (int) * cityNumber);
        genetic->chromosomes[i].cityNumber = cityNumber;
        genetic->chromosomes[i].calculateTotalDistance = &calculateTotalDistance;
        genetic->chromosomes[i].destroy = &destroyChromosome;
    }

    genetic->shuffle = &shuffleChromosomes;
    genetic->initGeneration = &initPopulation;
    genetic->destroy = &destroyGenetic;

    return genetic;
}

void destroyGenetic(Genetic * genetic) {
    int i = 0;
    for (i = 0; i < genetic->chromosomeNumber; i++) {
        destroyChromosome((genetic->chromosomes + i));
    }
    free(genetic-> chromosomes);
    free(genetic);
};

void shuffle(Chromosome * array, int n) {
    if (n > 1) {
        int i;
        for (i = 0; i < n; i++) {
            int j = rand() % n;
            Chromosome t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

void shuffleChromosomes(Genetic * genetic) {
    shuffle(genetic->chromosomes, genetic->chromosomeNumber);
}
