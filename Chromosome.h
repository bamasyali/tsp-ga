/* 
 * File:   Chromosome.h
 * Author: bamasyali
 *
 * Created on October 22, 2013, 4:00 PM
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

typedef struct ChromosomeStruct {
    int * values;
    int cityNumber;
    double totalDistance;

    void (*calculateTotalDistance)(struct ChromosomeStruct*, struct CityStruct * cities);
    void (*validate)(struct ChromosomeStruct*);
    void (*print)(struct ChromosomeStruct*);
    void (*destroy)(struct ChromosomeStruct*);
} Chromosome;

Chromosome * initChromosome(Chromosome * chromosome, int citySize);

Chromosome * initChromosome(int citySize);

Chromosome * readSolutionFromFile(FILE * file, int cityNumber);

void generateChromosomeUsingRandom(Chromosome * chromosome);

void generateChromosomeUsingNearestNeigbour(Chromosome * chromosome, City * cities);