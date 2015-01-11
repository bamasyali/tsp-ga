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


#define TOURNAMENT_SIZE 5

Chromosome ** performTournamentSelection(Chromosome * chromosomes, int chromosomeNumber) {

    Chromosome ** result = (Chromosome**) malloc(2 * sizeof (Chromosome*));

    int random = rand() % (chromosomeNumber - TOURNAMENT_SIZE);

    int best;
    long bestDistance = 99999999;
    int i;
    for (i = random; i < random + TOURNAMENT_SIZE; i++) {
        if (chromosomes[i].totalDistance < bestDistance) {
            best = i;
            bestDistance = chromosomes[i].totalDistance;
        }
    }

    result[0] = chromosomes + best;

    int best2 = best;

    while (best == best2) {

        random = rand() % (chromosomeNumber - (TOURNAMENT_SIZE));

        bestDistance = 99999999;
        for (i = random; i < random + TOURNAMENT_SIZE; i++) {
            if (chromosomes[i].totalDistance < bestDistance) {
                best2 = i;
                bestDistance = chromosomes[i].totalDistance;
            }
        }

    }

    result[1] = chromosomes + best2;

    return result;
}
