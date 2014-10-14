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
    long totalDistance;

    void (*calculateTotalDistance)(struct ChromosomeStruct*, struct CityStruct * cities);
    void (*destroy)(struct ChromosomeStruct*);

    void (*print)(struct ChromosomeStruct*);
    void (*validate)(struct ChromosomeStruct*);

} Chromosome;


Chromosome * initChromosome(int citySize);

void destroyChromosome(Chromosome * chromosome);

void calculateTotalDistance(Chromosome * chromosome, City * cities);

void printChromosome(Chromosome * chromosome);

void validateChromosome(Chromosome * chromosome);

Chromosome * readSolutionFromFile(FILE * file, int cityNumber);