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

#ifndef MEMORY_GENETIC_H
#define MEMORY_GENETIC_H 1
#include "MemoryGenetic.h"
#endif

void shuffleChromosomes(Chromosome * array, int size) {
    if (size > 1) {
        int i;
        for (i = 0; i < size; i++) {
            int j = rand() % size;
            Chromosome t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

void shuffleMemory(MemoryGenetic * genetic) {
    shuffleChromosomes(genetic->memoryPopulation, genetic->chromosomeNumber);
}

void shuffleSearch(MemoryGenetic * genetic) {
    shuffleChromosomes(genetic->searchPopulation, genetic->chromosomeNumber);
}

void replace(MemoryGenetic * genetic, Chromosome * child1, Chromosome * child2) {
    int worstFirst = 1;
    int worstSecond = 0;
    long worstFirstDistance = 0;
    long worstSecondDistance = 0;

    int i;
    for (i = 0; i < genetic->chromosomeNumber; i++) {
        if (genetic->memoryPopulation[i].totalDistance > worstFirstDistance) {
            worstSecond = worstFirst;
            worstFirst = i;
            worstSecondDistance = worstFirstDistance;
            worstFirstDistance = genetic->memoryPopulation[i].totalDistance;
        }
    }

    free(genetic->memoryPopulation[worstFirst].values);
    genetic->memoryPopulation[worstFirst].values = child1->values;
    genetic->memoryPopulation[worstFirst].totalDistance = child1->totalDistance;
    free(child1);

    free(genetic->memoryPopulation[worstSecond].values);
    genetic->memoryPopulation[worstSecond].values = child2->values;
    genetic->memoryPopulation[worstSecond].totalDistance = child2->totalDistance;
    free(child2);
}

void printMemory(MemoryGenetic * genetic, int generationNumber) {
    long best = 999999;
    long worst = 0;
    int j;
    for (j = 0; j < genetic->chromosomeNumber; j++) {
        if (genetic->memoryPopulation[j].totalDistance < best) {
            best = genetic->memoryPopulation[j].totalDistance;
        }
        if (genetic->memoryPopulation[j].totalDistance > worst) {
            worst = genetic->memoryPopulation[j].totalDistance;
        }
    }
    printf("%d ; %lu ; %lu\n", generationNumber, best, worst);
}

void printSearch(MemoryGenetic * genetic, int generationNumber) {
    long best = 999999;
    long worst = 0;
    int j;
    for (j = 0; j < genetic->chromosomeNumber; j++) {
        if (genetic->searchPopulation[j].totalDistance < best) {
            best = genetic->searchPopulation[j].totalDistance;
        }
        if (genetic->searchPopulation[j].totalDistance > worst) {
            worst = genetic->searchPopulation[j].totalDistance;
        }
    }
    printf("%d ; %lu ; %lu\n", generationNumber, best, worst);
}

void destroy(MemoryGenetic * genetic) {
    int i = 0;
    for (i = 0; i < genetic->chromosomeNumber; i++) {
        Chromosome * chromosome = genetic->memoryPopulation + i;
        chromosome->destroy(chromosome);

        chromosome = genetic->searchPopulation + i;
        chromosome->destroy(chromosome);

        chromosome = genetic->explicitMemory + i;
        chromosome->destroy(chromosome);

    }
    free(genetic-> memoryPopulation);
    free(genetic-> searchPopulation);
    free(genetic-> explicitMemory);
    free(genetic);
};

Chromosome * run(MemoryGenetic * genetic, CityTraffic * traffic) {

    //Init population
    {
        int i;
        int chromosomeSize = genetic->chromosomeNumber;

        for (i = 0; i < chromosomeSize; i++) {
            if (i % 2 == 0) {
                generateChromosomeUsingRandom(genetic->memoryPopulation + i);
                generateChromosomeUsingRandom(genetic->searchPopulation + i);
            } else {
                generateChromosomeUsingNearestNeigbour(genetic->memoryPopulation + i, genetic->cities);
                generateChromosomeUsingNearestNeigbour(genetic->searchPopulation + i, genetic->cities);
            }


            genetic->memoryPopulation[i].calculateTotalDistance(genetic->memoryPopulation + i, genetic->cities, traffic);
            genetic->memoryPopulation->validate(genetic->memoryPopulation + i);

            genetic->searchPopulation[i].calculateTotalDistance(genetic->searchPopulation + i, genetic->cities, traffic);
            genetic->searchPopulation->validate(genetic->searchPopulation + i);
        }
    }

    int i;
    for (i = 0; i < genetic->generationLimit; i++) {

        int j;
        for (j = 0; j < 10; j++) {
            genetic->shuffleMemory(genetic);

            Chromosome ** selection = genetic->selection(genetic->memoryPopulation, genetic->chromosomeNumber);

            Chromosome * c1 = selection[0];
            Chromosome * c2 = selection[1];

            Chromosome ** children = genetic->crossover(c1, c2, genetic->cityNumber);

            Chromosome * child1 = children[0];
            Chromosome * child2 = children[1];


            int random = rand() % 100;
            if (random < genetic->mutationProbablity) {
                genetic->mutation(child1);
            }

            random = rand() % 100;
            if (random < genetic->mutationProbablity) {
                genetic->mutation(child2);
            }

            child1->calculateTotalDistance(child1, genetic->cities, traffic);
            child2->calculateTotalDistance(child2, genetic->cities, traffic);

            genetic->replace(genetic, child1, child2);

            genetic->generation++;
        }




        for (j = 0; j < 10; j++) {
            int k;
            for (k = 0; k < genetic->chromosomeNumber; k++) {
                Chromosome * chromosome = genetic->searchPopulation + k;
                Chromosome * clone = chromosome->clone(chromosome);
                genetic->mutation(clone);
                clone->calculateTotalDistance(clone, genetic->cities, traffic);
                if (clone->totalDistance < chromosome->totalDistance) {
                    free(chromosome->values);
                    chromosome->values = clone->values;
                    chromosome->totalDistance = clone->totalDistance;
                    chromosome->cityNumber = clone->cityNumber;
                    free(clone);
                } else {
                    clone->destroy(clone);
                }
            }
        }





        long best = 999999;
        Chromosome * bestChromosome;
        for (j = 0; j < genetic->chromosomeNumber; j++) {
            if (genetic->memoryPopulation[j].totalDistance < best) {
                best = genetic->memoryPopulation[j].totalDistance;
                bestChromosome = genetic->memoryPopulation + j;
            }

            if (genetic->searchPopulation[j].totalDistance < best) {
                best = genetic->searchPopulation[j].totalDistance;
                bestChromosome = genetic->searchPopulation + j;
            }
        }

        if (i > 0 && i % 1000 == 0) {
            traffic++;
            for (j = 0; j < genetic->chromosomeNumber; j++) {
                genetic->memoryPopulation->calculateTotalDistance(genetic->memoryPopulation + j, genetic->cities, traffic);
                genetic->searchPopulation->calculateTotalDistance(genetic->searchPopulation + j, genetic->cities, traffic);
            }

            for (j = 0; j < genetic->explicitMemorySize; j++) {
                genetic->explicitMemory->calculateTotalDistance(genetic->explicitMemory + j, genetic->cities, traffic);
            }

            for (j = 0; j < genetic->chromosomeNumber; j++) {
                if (j % 2 == 0) {
                    generateChromosomeUsingRandom(genetic->searchPopulation + j);
                } else {
                    generateChromosomeUsingNearestNeigbour(genetic->searchPopulation + j, genetic->cities);
                }
                genetic->searchPopulation[j].calculateTotalDistance(genetic->searchPopulation + j, genetic->cities, traffic);
                genetic->searchPopulation->validate(genetic->searchPopulation +j);
            }


        }


        genetic->printMemory(genetic, i);
        genetic->printSearch(genetic, i);



        if (i % genetic->memoryUpdateFrequency == 0) {
            if (genetic->explicitMemorySize < genetic->chromosomeNumber) {

                Chromosome * clone = bestChromosome->clone(bestChromosome);
                genetic->explicitMemory[genetic->explicitMemorySize].values = clone->values;
                genetic->explicitMemory[genetic->explicitMemorySize].totalDistance = clone->totalDistance;
                free(clone);
            } else {
                long worst = 0;
                Chromosome * worstChromosome;
                for (j = 0; j < genetic->chromosomeNumber; j++) {
                    if (genetic->explicitMemory[j].totalDistance > worst) {
                        worst = genetic->explicitMemory[j].totalDistance;
                        worstChromosome = genetic->memoryPopulation + j;
                    }
                }

                Chromosome * clone = bestChromosome->clone(bestChromosome);
                worstChromosome->values = clone->values;
                worstChromosome->totalDistance = clone->totalDistance;
                free(clone);
            }
        }


    }
}

MemoryGenetic * initMemoryGenetic(int cityNumber, int generationLimit, int chromosomeNumber, City * cities, int memoryUpdateFrequency) {
    MemoryGenetic * genetic = (MemoryGenetic *) malloc(sizeof (MemoryGenetic));

    genetic->cityNumber = cityNumber;
    genetic->generation = 0;
    genetic->generationLimit = generationLimit;
    genetic->chromosomeNumber = chromosomeNumber;
    genetic->memoryPopulation = (Chromosome *) malloc(sizeof (Chromosome) * chromosomeNumber);
    genetic->searchPopulation = (Chromosome *) malloc(sizeof (Chromosome) * chromosomeNumber);
    genetic->explicitMemory = (Chromosome *) malloc(sizeof (Chromosome) * chromosomeNumber);
    genetic->cities = cities;
    genetic->memoryUpdateFrequency = memoryUpdateFrequency;
    genetic->explicitMemorySize = 0;

    int i;
    for (i = 0; i < chromosomeNumber; i++) {
        Chromosome * chromosome = genetic->memoryPopulation + i;
        initChromosome(chromosome, cityNumber);

        chromosome = genetic->searchPopulation + i;
        initChromosome(chromosome, cityNumber);

        chromosome = genetic->explicitMemory + i;
        initChromosome(chromosome, cityNumber);
    }

    genetic->shuffleMemory = &shuffleMemory;
    genetic->shuffleSearch = &shuffleSearch;
    genetic->replace = &replace;
    genetic->destroy = &destroy;
    genetic->printMemory = &printMemory;
    genetic->printSearch = &printSearch;
    genetic->run = &run;


    return genetic;
}


