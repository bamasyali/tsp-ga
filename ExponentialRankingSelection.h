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

void initRanks(Genetic * genetic);

Chromosome ** performExponentialRankingSelection(Genetic * genetic);