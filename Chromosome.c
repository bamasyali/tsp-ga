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

void calculateTotalDistance(Chromosome * chromosome, City * cities) {

    double totalDistance = 0;

    int i;
    for (i = 0; i < chromosome->cityNumber - 1; i++) {
        int cityId1 = chromosome->values[i];
        int cityId2 = chromosome->values[i + 1];
        City * c1 = cities + cityId1;
        City * c2 = cities + cityId2;
        //printf("%d %d %d\n", i, c1->id, c2->id);
        totalDistance += cities->calculateDistanceById(cities, c1->id, c2->id);
    }

    int cityId1 = chromosome->values[chromosome->cityNumber - 1];
    int cityId2 = chromosome->values[0];
    City * c1 = cities + cityId1;
    City * c2 = cities + cityId2;
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

Chromosome * cloneChromosome(Chromosome * chromosome) {
    Chromosome * clone = initChromosome(chromosome->cityNumber);
    int i;
    for (i = 0; i < chromosome->cityNumber; i++) {
        clone->values[i] = chromosome->values[i];
    }
    clone->totalDistance = chromosome->totalDistance;
    return clone;
}

Chromosome * initChromosome(Chromosome * chromosome, int cityNumber) {
    chromosome->values = (int*) malloc(sizeof (int) * cityNumber);
    chromosome->cityNumber = cityNumber;

    chromosome->calculateTotalDistance = &calculateTotalDistance;
    chromosome->clone = &cloneChromosome;
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

void generateChromosomeUsingRandom(Chromosome * chromosome) {

    int i;
    for (i = 0; i < chromosome->cityNumber; i++) {
        chromosome->values[i] = i + 1;
    }

    shuffleCityArray(chromosome->values, chromosome->cityNumber);
}

void generateChromosomeUsingNearestNeigbour(Chromosome * chromosome, City * cities) {

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


            double distance = cities->calculateDistance(cities + city, cities + i);

            if (distance < minDistance) {
                minDistance = distance;
                nearestCity = i;
            }
        }

        chromosome->values[index++] = nearestCity;
    }
}
