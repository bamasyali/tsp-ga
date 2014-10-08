/* 
 * File:   ExponentialRankingSelection.h
 * Author: bamasyali
 *
 * Created on November 3, 2013, 11:46 AM
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

#ifndef RANKING_H
#define RANKING_H 1
#include "ExponentialRankingSelection.h"
#endif

#include <math.h>

#define E 2.71828

double * ranks;
double * rankProbablities;

void initRanks(Genetic * genetic) {
    ranks = (double *) malloc(genetic->chromosomeNumber * sizeof (double));
    rankProbablities = (double *) malloc(genetic->chromosomeNumber * sizeof (double));

    ranks[0] = 1;

    double count = 0;

    for (int i = 0; i < genetic->chromosomeNumber; i++) {
        ranks[i] = (1 - pow(E, -(i + 1)));
        count += ranks[i];
    }


    for (int i = 0; i < genetic->chromosomeNumber; i++) {
        ranks[i] = ranks[i] / count;
        rankProbablities[i] = i == 0 ? ranks[i] : rankProbablities[i - 1] + ranks[i];
        //printf("%lf\n", rankProbablities[i]);
    }
}

Chromosome ** performExponentialRankingSelection(Genetic * genetic) {

    Chromosome ** result = (Chromosome**) malloc(2 * sizeof (Chromosome*));

    int i;
    for (i = 0; i < genetic->chromosomeNumber; i++) {
        for (int j = i + 1; j < genetic->chromosomeNumber; j++) {
            if (genetic->chromosomes[i].totalDistance < genetic->chromosomes[j].totalDistance) {
                Chromosome temp = genetic->chromosomes[i];
                genetic->chromosomes[i] = genetic->chromosomes[j];
                genetic->chromosomes[j] = temp;
            }
        }
    }

    int random = rand() % 10000000;
    double rank = ((double) random) / 10000000;

    for (i = 0; i < genetic->chromosomeNumber; i++) {
        if (rank < rankProbablities[i]) {
            result[0] = genetic->chromosomes + i;
            break;
        }
    }

    rank = rank + 0.5;
    if (rank > 1) {
        rank = rank - 1;
    }


    for (i = 0; i < genetic->chromosomeNumber; i++) {
        if (rank <= rankProbablities[i]) {
            result[1] = genetic->chromosomes + i;
            break;
        }
    }

    return result;

}
