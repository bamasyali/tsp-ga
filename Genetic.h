/* 
 * File:   Genetic.h
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

#ifndef CHROMOSOME_H
#define CHROMOSOME_H 1
#include "Chromosome.h"
#endif

typedef struct GeneticStruct {
    int cityNumber; //City size
    int generation;
    int generationLimit;
    int chromosomeNumber; // Chromosome number
    int mutationProbablity;
    Chromosome * chromosomes;
    City * cities;

    void (*initPopulation)(struct GeneticStruct*, double randomNeighbourRatio);
    void (*shuffle)(struct GeneticStruct*);
    Chromosome ** (*selection)(Chromosome * chromosomes, int chromosomeNumber);
    Chromosome ** (*crossover)(Chromosome * c1, Chromosome * c2, int cityNumber);
    void (*replace)(struct GeneticStruct*, Chromosome *, Chromosome *);
    void (*mutation)(struct ChromosomeStruct*);
    void (*destroy)(struct GeneticStruct*);
    void (*print)(struct GeneticStruct*, int generationNumber);
    Chromosome * (*run)(struct GeneticStruct*);

} Genetic;

Genetic * initGenetic(int citySize, int generationLimit, int chromosomeSize, City * cities);


