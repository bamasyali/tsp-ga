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

typedef struct MemoryGeneticStruct {
    int cityNumber; //City size
    int generation;
    int generationLimit;
    int chromosomeNumber; // Chromosome number
    int mutationProbablity;
    int memoryUpdateFrequency;
    Chromosome * searchPopulation;
    Chromosome * memoryPopulation;
    Chromosome * explicitMemory;
    City * cities;

    void (*initPopulation)(struct MemoryGeneticStruct*, double randomNeighbourRatio);
    void (*shuffleMemory)(struct MemoryGeneticStruct*);
    void (*shuffleSearch)(struct MemoryGeneticStruct*);
    Chromosome ** (*selection)(Chromosome * chromosomes, int chromosomeNumber);
    Chromosome ** (*crossover)(struct MemoryGeneticStruct*, Chromosome *, Chromosome *);
    void (*replace)(struct MemoryGeneticStruct*, Chromosome *, Chromosome *);
    void (*mutation)(struct ChromosomeStruct*);
    void (*destroy)(struct MemoryGeneticStruct*);
    void (*print)(struct MemoryGeneticStruct*, int generationNumber);
    Chromosome * (*run)(struct MemoryGeneticStruct*);

} MemoryGenetic;

MemoryGenetic * initMemoryGenetic(int citySize, int generationLimit, int chromosomeSize, City * cities);


