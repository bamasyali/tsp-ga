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

#include <math.h>

#define nint(a)   ((a) >= 0.0 ? (int)((a)+0.5) : (int)((a)-0.5))

City * initCity() {
    City * city = (City*) malloc(sizeof (City));
    city->destroy = &destroyCity;
    city->print = &printCity;
    return city;
}

City * initCityWithValues(int id, double lat, double lng) {
    City * city = (City*) malloc(sizeof (City));
    city->id = id;
    city->lat = lat;
    city->lng = lng;
    city->destroy = &destroyCity;
    city->print = &printCity;
    return city;
}

void destroyCity(City * city) {
    free(city);
}

void printCity(City * city) {
    printf("id=%d, lat=%lf, lng=%lf\n", city->id, city->lat, city->lng);
}

City * readCitiesFromFile(FILE * file, int cityNumber) {
    int i;
    int id;
    double lat;
    double lng;

    City * city = (City*) malloc(sizeof (City) * cityNumber);
    City * temp = city;

    for (i = 0; i < cityNumber; i++) {
        fscanf(file, "%d", &id);
        fscanf(file, "%lf", &lat);
        fscanf(file, "%lf", &lng);

        temp->id = id;
        temp->lat = lat;
        temp->lng = lng;
        temp->print = &printCity;
        temp->destroy = &destroyCity;

        temp++;
    }

    return city;
}

inline double calculateDistance(City* city1, City* city2) {
    double lat = city1->lat - city2->lat;
    lat = lat * lat;

    double lng = city1->lng - city2->lng;
    lng = lng * lng;

    double temp = lat + lng;

    return nint(sqrt(temp));
}

double calculateDistanceById(City * cities, int city1, int city2) {
    City * c1 = (cities + city1 - 1);
    City * c2 = (cities + city2 - 1);

    return calculateDistance(c1, c2);
}
