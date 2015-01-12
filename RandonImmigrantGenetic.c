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
#include "RandonImmigrantGenetic.h"
#endif

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
    printf("%d ; %lu; %lu\n", generationNumber, best, worst);
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

Chromosome * run(Genetic * genetic) {
    int i;

    int chromosomeSize = genetic->chromosomeNumber;
    for (i = 0; i < chromosomeSize; i++) {
        generateChromosomeUsingRandom(genetic->chromosomes + i);

        genetic->chromosomes[i].calculateTotalDistance(genetic->chromosomes + i, *genetic->cities);
        genetic->chromosomes->validate(genetic->chromosomes + i);
    }


    for (i = 0; i < genetic->generationLimit; i++) {

        genetic->shuffle(genetic);

        Chromosome ** selection = genetic->selection(genetic->chromosomes, genetic->chromosomeNumber);

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

        child1->calculateTotalDistance(child1, *genetic->cities);
        child2->calculateTotalDistance(child2, *genetic->cities);

        genetic->replace(genetic, child1, child2);

        genetic->generation++;


        if (i > 0 && i % 1000 == 0) {

            genetic->cities++;

            int j;
            for (j = 0; j < genetic->chromosomeNumber; j++) {
                genetic->chromosomes->calculateTotalDistance(genetic->chromosomes + j, *genetic->cities);
            }

            for (j = 0; j < genetic->chromosomeNumber * genetic->replacementRate; j++) {
                generateChromosomeUsingRandom(genetic->chromosomes + j);

                genetic->chromosomes[j].calculateTotalDistance(genetic->chromosomes + j, *genetic->cities);
                genetic->chromosomes->validate(genetic->chromosomes + j);
            }
        }

        print(genetic, i);
    }

    long best = 999999;
    Chromosome * bestChromosome;
    int j;
    for (j = 0; j < genetic->chromosomeNumber; j++) {
        if (genetic->chromosomes[j].totalDistance < best) {
            best = genetic->chromosomes[j].totalDistance;
            bestChromosome = genetic->chromosomes + j;
        }
    }
    return bestChromosome;
}

Genetic * initGenetic(int cityNumber, int generationLimit, int chromosomeNumber, City ** cities, double replacementRate) {
    Genetic * genetic = (Genetic *) malloc(sizeof (Genetic));

    genetic->cityNumber = cityNumber;
    genetic->generation = 0;
    genetic->generationLimit = generationLimit;
    genetic->chromosomeNumber = chromosomeNumber;
    genetic->chromosomes = (Chromosome *) malloc(sizeof (Chromosome) * chromosomeNumber);
    genetic->cities = cities;
    genetic->replacementRate = replacementRate;

    int i;
    for (i = 0; i < chromosomeNumber; i++) {
        Chromosome * chromosome = genetic->chromosomes + i;
        initChromosome(chromosome, cityNumber);
    }

    genetic->shuffle = &shuffle;
    genetic->replace = &replace;
    genetic->destroy = &destroy;
    genetic->print = &print;
    genetic->run = &run;


    return genetic;
}


