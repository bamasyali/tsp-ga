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

void initPopulation(Genetic * genetic, double randomNeighbourRatio) {
    int i;
    int chromosomeSize = genetic->chromosomeNumber;
    int randomChromosomeNumber = randomNeighbourRatio * chromosomeSize;

    for (i = 0; i < chromosomeSize; i++) {
        if (i < randomChromosomeNumber) {
            generateChromosomeUsingRandom(genetic->chromosomes + i);
        } else {
            generateChromosomeUsingNearestNeigbour(genetic->chromosomes + i, genetic->cities);
        }
        genetic->chromosomes[i].calculateTotalDistance(genetic->chromosomes + i, genetic->cities);
        genetic->chromosomes->validate(genetic->chromosomes + i);
    }
}

void shuffle(Genetic * genetic) {
    Chromosome * array = genetic->chromosomes;
    int n = genetic->chromosomeNumber;

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

void replace(Genetic * genetic, Chromosome * child1, Chromosome * child2) {
    int worstFirst = 1;
    int worstSecond = 0;
    long worstFirstDistance = 0;
    long worstSecondDistance = 0;

    int i;
    for (i = 0; i < genetic->chromosomeNumber; i++) {
        if (genetic->chromosomes[i].totalDistance > worstFirstDistance) {
            worstSecond = worstFirst;
            worstFirst = i;
            worstSecondDistance = worstFirstDistance;
            worstFirstDistance = genetic->chromosomes[i].totalDistance;
        }
    }

    free(genetic->chromosomes[worstFirst].values);
    genetic->chromosomes[worstFirst].values = child1->values;
    genetic->chromosomes[worstFirst].totalDistance = child1->totalDistance;
    free(child1);

    free(genetic->chromosomes[worstSecond].values);
    genetic->chromosomes[worstSecond].values = child2->values;
    genetic->chromosomes[worstSecond].totalDistance = child2->totalDistance;
    free(child2);
}

void print(Genetic * genetic, int generationNumber) {
    long best = 999999;
    long worst = 0;
    int j;
    for (j = 0; j < genetic->chromosomeNumber; j++) {
        if (genetic->chromosomes[j].totalDistance < best) {
            best = genetic->chromosomes[j].totalDistance;
        }
        if (genetic->chromosomes[j].totalDistance > worst) {
            worst = genetic->chromosomes[j].totalDistance;
        }
    }

    long average = 0;
    for (j = 0; j < genetic->chromosomeNumber; j++) {
        average += genetic->chromosomes[j].totalDistance;
    }
    average = average / genetic->chromosomeNumber;
    printf("GA ; %d ; %lu ; %lu ; %lu\n", generationNumber, best, average, worst);
}

void destroy(Genetic * genetic) {
    int i = 0;
    for (i = 0; i < genetic->chromosomeNumber; i++) {
        Chromosome * chromosome = genetic->chromosomes + i;
        chromosome->destroy(chromosome);
    }
    free(genetic-> chromosomes);
    free(genetic);
};

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
        Chromosome * chromosome = genetic->chromosomes + i;
        initChromosome(chromosome, cityNumber);
    }

    genetic->initPopulation = &initPopulation;
    genetic->shuffle = &shuffle;
    genetic->replace = &replace;
    genetic->destroy = &destroy;
    genetic->print = &print;


    return genetic;
}

