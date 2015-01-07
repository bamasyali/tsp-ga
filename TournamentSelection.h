/* 
 * File:   tournamentSelection.h
 * Author: bamasyali
 *
 * Created on October 22, 2013, 4:13 PM
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

Chromosome ** performTournamentSelection(Chromosome * chromosomes, int chromosomeNumber);