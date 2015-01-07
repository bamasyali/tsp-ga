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

void printCity(City * city) {
    printf("id=%d, lat=%lf, lng=%lf\n", city->id, city->lat, city->lng);
}

void destroyCity(City * city) {
    free(city);
}

City * initCity() {
    City * city = (City*) malloc(sizeof (City));
    city->calculateDistance = &calculateDistance;
    city->calculateDistanceById = &calculateDistanceById;
    city->print = &printCity;
    city->destroy = &destroyCity;
    return city;
}

CityTraffic * initCityTraffic(int cityNumber) {
    CityTraffic * cityTraffic = (CityTraffic*) malloc(sizeof (CityTraffic));
    cityTraffic->traffic = (double*) malloc(sizeof (double) * cityNumber * cityNumber);

    int i;
    for (i = 0; i < cityNumber * cityNumber; i++) {
        cityTraffic->traffic[i] = 1;
    }

    return cityTraffic;
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

        city->calculateDistance = &calculateDistance;
        city->calculateDistanceById = &calculateDistanceById;
        temp->print = &printCity;
        temp->destroy = &destroyCity;

        temp++;
    }

    return city;
}

CityTraffic * readCityTrafficFromFile(FILE * file, int cityNumber) {
    int city1;
    int city2;
    double traffic;

    CityTraffic * cityTraffic = initCityTraffic(cityNumber);

    int i;
    for (i = 0; i < 11; i++) {
        fscanf(file, "%d", &city1);
        fscanf(file, "%d", &city2);
        fscanf(file, "%lf", &traffic);

        cityTraffic->traffic[city1 * cityNumber + city2] = traffic;
    }

    return cityTraffic;
}


