/* 
 * File:   PartiallyMappedCrossover.c
 * Author: bamasyali
 *
 * Created on October 27, 2013, 15:27 PM
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
#endif

Chromosome * crossover(Chromosome * c1, Chromosome * c2, int s1, int s2) {
    int cityNumber = c1->cityNumber;

    Chromosome * newChromosome = initChromosome(cityNumber);

    int i;
    for (i = 0; i < cityNumber; i++) {
        newChromosome->values[i] = -1;
    }

    for (i = s1; i < s2; i++) {
        newChromosome->values[i] = c1->values[i];
    }

    for (i = s1; i < s2; i++) {
        int temp = c2->values[i];

        int j;
        int exists = 0;
        for (j = s1; j < s2; j++) {
            if (temp == newChromosome->values[j]) {
                exists = 1;
                break;
            }
        }

        if (exists == 1) {
            continue;
        }

        exists = 0;

        int valueAtTempsPlaceInNewChromosome = newChromosome->values[i];

label:

        for (j = 0; j < cityNumber; j++) {
            if (c2->values[j] == valueAtTempsPlaceInNewChromosome) {
                if (j < s1 || j > s2 - 1) {
                    newChromosome->values[j] = temp;
                } else {
                    exists = 1;
                    valueAtTempsPlaceInNewChromosome = c1->values[j];
                    goto label;
                }
                break;
            }
        }
    }

    for (i = 0; i < cityNumber; i++) {
        if (newChromosome->values[i] == -1) {
            newChromosome->values[i] = c2->values[i];
        }
    }





    /*
            for (int j = 0; j < 150; j++) {
                int asd = 0;
                for (int k = j + 1; k < 150; k++) {
                    if (newChromosome->values[j] != -1 && newChromosome->values[j] == newChromosome->values[k]) {
                        printf("Hata! %d %d %d\n\n", j, k, newChromosome->values[j]);
                    }
                    if (newChromosome->values[j] == k + 1) {
                        asd = 1;
                    }
                }
                if (asd = 0) {
                    printf("Hata! %d", newChromosome->values[i]);
                }
            }
     */




    /*
        for (int l = 0; l < 150; l++) {
            printf("%d\n", newChromosome->values[l]);
        }
        printf("\n\n");
     */


    /*
        for (int j = 0; j < 150; j++) {
            for (int k = j + 1; k < 150; k++) {
                if (newChromosome->values[j] != -1 && newChromosome->values[j] == newChromosome->values[k]) {
                    printf("s1 %d\n", s1);
                    printf("s2 %d\n\n", s2);
                    for (int l = 0; l < 150; l++) {
                        printf("%d,", c1->values[l]);
                    }
                    printf("\n\n", s2);
                    for (int l = 0; l < 150; l++) {
                        printf("%d,", c2->values[l]);
                    }
                    printf("\n\n", s2);

                    for (int l = 0; l < 150; l++) {
                        printf("%d,", newChromosome->values[l]);
                    }
                    printf("\n\n", s2);

                }
            }
        }
     */


    return newChromosome;
}

void performCrossover(Genetic * genetic, Chromosome * c1, Chromosome * c2) {

    int s1 = rand() % genetic->cityNumber;
    //printf("%d", s1);
    int s2 = s1 + rand() % (genetic->cityNumber - s1);
    //printf(" %d\n", s2);


    Chromosome * child1 = crossover(c1, c2, s1, s2);
    Chromosome * child2 = crossover(c2, c1, s1, s2);

    int random = rand() % 100;
    if (random < 10) {
        genetic->mutation(child1);
    }

    random = rand() % 100;
    if (random < 10) {
        genetic->mutation(child2);
    }

    child1->calculateTotalDistance(child1, genetic->cities);
    child2->calculateTotalDistance(child2, genetic->cities);

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

