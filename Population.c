#ifndef LIBS
#define LIBS 1
#include <stdio.h>
#include <stdlib.h>
#endif

#ifndef CITY_H
#define CITY_H 1
#include "City.h"
#endif

#ifndef GENETIC_H
#define GENETIC_H 1
#include "Genetic.h"
#endif

#ifndef CHROMOSOME_H
#define CHROMOSOME_H 1
#include "Chromosome.h"
#endif

#ifndef POPULATION_H
#define POPULATION_H 1
#include "Population.h"
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

void generateChromosomeUsingRandom(Genetic * genetic, Chromosome * chromosome) {

    int i;
    for (i = 0; i < chromosome->cityNumber; i++) {
        chromosome->values[i] = i + 1;
    }

    shuffle(chromosome->values, chromosome->cityNumber);
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

void initPopulation(Genetic * genetic) {
    int i;
    int chromosomeSize = genetic->chromosomeNumber;
    for (i = 0; i < chromosomeSize; i++) {
        generateChromosomeUsingNearestNeigbour(genetic, genetic->chromosomes + i);
        genetic->chromosomes[i].calculateTotalDistance(genetic->chromosomes + i, genetic->cities);
    }
}
