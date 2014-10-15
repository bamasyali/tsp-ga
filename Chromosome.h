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

void initChromosome(Chromosome * chromosome, int citySize);

Chromosome * initChromosome(int citySize);

Chromosome * readSolutionFromFile(FILE * file, int cityNumber);