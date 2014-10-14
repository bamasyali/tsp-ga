/* 
 * File:   PartiallyMappedCrossover.h
 * Author: bamasyali
 *
 * Created on October 25, 2013, 9:13 PM
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

 Chromosome ** performCrossover(Genetic * genetic, Chromosome * c1, Chromosome * c2);