/* 
 * File:   RankingSelection.h
 * Author: bamasyali
 *
 * Created on October 27, 2013, 4:56 PM
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

#ifndef GENETIC_h
#define GENETIC_H 1
#include "Genetic.h"
#endif


#define TOURNAMENT_SIZE 5

Chromosome ** performTournamentSelection(Genetic * genetic) {

    Chromosome ** result = (Chromosome**) malloc(2 * sizeof (Chromosome*));

    int random = rand() % (genetic->chromosomeNumber - (TOURNAMENT_SIZE * 2));

    int best;
    long bestDistance = 99999999;
    int i;
    for (i = random; i < random + TOURNAMENT_SIZE; i++) {
        if (genetic->chromosomes[i].totalDistance < bestDistance) {
            best = i;
            bestDistance = genetic->chromosomes[i].totalDistance;
        }
    }

    result[0] = genetic->chromosomes + best;

    bestDistance = 99999999;
    for (i = random + TOURNAMENT_SIZE; i < random + (TOURNAMENT_SIZE * 2); i++) {
        if (genetic->chromosomes[i].totalDistance < bestDistance) {
            best = i;
            bestDistance = genetic->chromosomes[i].totalDistance;
        }
    }

    result[1] = genetic->chromosomes + best;

    return result;
}
