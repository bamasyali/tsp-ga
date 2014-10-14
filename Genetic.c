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
        genetic->chromosomes[i].print = &printChromosome;
        genetic->chromosomes[i].validate = &validateChromosome;
    }

    genetic->initPopulation = &initPopulation;
    genetic->replace = &replace;
    genetic->shuffle = &shuffleChromosomes;
    genetic->destroy = &destroyGenetic;
    genetic->print = &printGeneration;


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

void shuffleCityArray(int *array, int n) {
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

void generateChromosomeUsingRandom(Genetic * genetic, Chromosome * chromosome) {

    int i;
    for (i = 0; i < chromosome->cityNumber; i++) {
        chromosome->values[i] = i + 1;
    }

    shuffleCityArray(chromosome->values, chromosome->cityNumber);
}

void generateChromosomeUsingNearestNeigbour(Genetic * genetic, Chromosome * chromosome) {

    int i;
    for (i = 0; i < chromosome->cityNumber; i++) {
        chromosome->values[i] = -1;
    }

    int index = 0;

    int city = rand() % chromosome->cityNumber;
    chromosome->values[index++] = city;

    while (index < chromosome->cityNumber) {

        double minDistance = 999999999;
        int nearestCity = -1;

        for (i = 0; i < chromosome->cityNumber; i++) {

            if (i == city) {
                continue;
            }

            int cont = 0;

            int j;
            for (j = 0; j < index; j++) {
                if (i == chromosome->values[j]) {
                    cont = 1;
                    break;
                }
            }

            if (cont == 1) {
                continue;
            }


            double distance = calculateDistance(genetic->cities + city, genetic->cities + i);

            if (distance < minDistance) {
                minDistance = distance;
                nearestCity = i;
            }
        }

        chromosome->values[index++] = nearestCity;
    }



}

void initPopulation(Genetic * genetic, double randomNeighbourRatio) {
    int i;
    int chromosomeSize = genetic->chromosomeNumber;
    int randomChromosomeNumber = randomNeighbourRatio * chromosomeSize;

    for (i = 0; i < chromosomeSize; i++) {
        if (i < randomChromosomeNumber) {
            generateChromosomeUsingRandom(genetic, genetic->chromosomes + i);
        } else {
            generateChromosomeUsingNearestNeigbour(genetic, genetic->chromosomes + i);
        }
        genetic->chromosomes[i].calculateTotalDistance(genetic->chromosomes + i, genetic->cities);
        validateChromosome(genetic->chromosomes + i);
    }
}

void printGeneration(Genetic * genetic, int generationNumber) {
    long best = 999999;
    int j;
    for (j = 0; j < genetic->chromosomeNumber; j++) {
        if (genetic->chromosomes[j].totalDistance < best) {
            best = genetic->chromosomes[j].totalDistance;
        }
    }

    long average = 0;
    for (j = 0; j < genetic->chromosomeNumber; j++) {
        average += genetic->chromosomes[j].totalDistance;
    }
    average = average / genetic->chromosomeNumber;
    printf("%d ; %lu ; %lu\n", generationNumber + 1, best, average);
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