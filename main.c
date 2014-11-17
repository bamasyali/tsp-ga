/* 
 * File:   main.c
 * Author: bamasyali
 *
 * Created on October 22, 2013, 3:58 PM
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

#ifndef GENETIC_H
#define GENETIC_H 1
#include "Genetic.h"
#endif


#ifndef PMC_H
#define PMC_H 1
#include "PartiallyMappedCrossover.h"
#include "TournamentSelection.h"
#endif

#ifndef SWAP_H
#define SWAP_H 1
#include "SwapMutation.h"
#endif

#ifndef INSERT_H
#define INSERT_H 1
#include "InsertMutation.h"
#endif

#ifndef INVERSION_H
#define INVERSION_H 1
#include "InversionMutation.h"
#endif

#ifndef RANDOM_H
#define RANDOM_H 1
#include "RandomMutation.h"
#endif

#ifndef RANKING_H
#define RANKING_H 1
#include "ExponentialRankingSelection.h"
#endif

#ifndef DISPLACEMENT_H
#define DISPLACEMENT 1
#include "InvertedDisplacementMutation.h"
#endif

#define CITY_COUNT 101
#define MUTATION_PROBABILITY 10
#define GENERATION_LIMIT 5000

City * CITY_LIST;

int main(int argc, char** argv) {

    if (argc != 6) {
        printf("Invalid Arguments!\n");
        return (EXIT_FAILURE);
    }

    char * chromosomeNumberArgument = argv[1];
    char * randomNeighbourRatioArgument = argv[2];
    char * selectionTypeArgument = argv[3];
    char * mutationTypeArgument = argv[4];
    char * srandArgument = argv[5];

    int chromosomeNumber;
    double randomNeighbourRatio;
    int selectionType;
    int mutationType;
    int sr;


    sscanf(chromosomeNumberArgument, "%d", &chromosomeNumber);
    sscanf(randomNeighbourRatioArgument, "%lf", &randomNeighbourRatio);
    sscanf(selectionTypeArgument, "%d", &selectionType);
    sscanf(mutationTypeArgument, "%d", &mutationType);
    sscanf(srandArgument, "%d", &sr);

    srand(sr);

    FILE * file = fopen("eil101.tsp", "r");
    CITY_LIST = readCitiesFromFile(file, CITY_COUNT);

    Genetic * genetic = initGenetic(CITY_COUNT, GENERATION_LIMIT, chromosomeNumber, CITY_LIST);
    genetic->crossover = &performPartiallyMappedCrossover;
    genetic->initPopulation(genetic, randomNeighbourRatio);


    if (selectionType == 1) {
        genetic->selection = &performTournamentSelection;
    } else if (selectionType == 2) {
        initRanks(genetic);
        genetic->selection = &performExponentialRankingSelection;
    }

    if (mutationType == 1) {
        genetic->mutation = &performSwapMutation;
    } else if (mutationType == 2) {
        genetic->mutation = &performInsertMutation;
    } else if (mutationType == 3) {
        genetic->mutation = &performInversionMutation;
    } else if (mutationType == 4) {
        genetic->mutation = &performRandomMutation;
    } else if (mutationType == 5) {
        genetic->mutation = &performInvertedDisplacementMutation;
    }

    int i;
    for (i = 0; i < genetic->generationLimit; i++) {

        genetic->shuffle(genetic);

        Chromosome ** selection = genetic->selection(genetic);

        Chromosome * c1 = selection[0];
        Chromosome * c2 = selection[1];

        Chromosome ** children = genetic->crossover(genetic, c1, c2);

        Chromosome * child1 = children[0];
        Chromosome * child2 = children[1];


        int random = rand() % 100;
        if (random < MUTATION_PROBABILITY) {
            genetic->mutation(child1);
        }

        random = rand() % 100;
        if (random < MUTATION_PROBABILITY) {
            genetic->mutation(child2);
        }

        child1->calculateTotalDistance(child1, genetic->cities);
        child2->calculateTotalDistance(child2, genetic->cities);

        genetic->replace(genetic, child1, child2);

        genetic->generation++;
    }

    genetic->destroy;

    return (EXIT_SUCCESS);
}

