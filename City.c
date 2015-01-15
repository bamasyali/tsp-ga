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

City * getCityById(City * cities, int size, int id) {
    for (int i = 0; i < size; i++) {
        if ((cities + i)->id == id) {
            return cities + i;
        }
    }
    return NULL;
}

double calculateDistanceById(City * cities, int size, int city1, int city2) {
    City * c1 = getCityById(cities, size, city1);
    City * c2 = getCityById(cities, size, city2);

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

City ** readCitiesFromFile(FILE * file, int cityNumber) {


    int fileNumber;
    fscanf(file, "%d", &fileNumber);

    City ** citiesList = (City **) malloc(fileNumber * sizeof (City*));

    int j;
    for (j = 0; j < fileNumber; j++) {

        char fileName[20];
        fscanf(file, "%s", fileName);
        printf("%s\n", fileName);

        FILE * cityFile = fopen(fileName, "r");

        int i;
        int id;
        double lat;
        double lng;

        citiesList[j] = (City*) malloc(sizeof (City) * cityNumber);
        City * temp = citiesList[j];

        for (i = 0; i < cityNumber; i++) {
            fscanf(cityFile, "%d", &id);
            fscanf(cityFile, "%lf", &lat);
            fscanf(cityFile, "%lf", &lng);

            temp->id = id;
            temp->lat = lat;
            temp->lng = lng;

            temp->calculateDistance = &calculateDistance;
            temp->calculateDistanceById = &calculateDistanceById;
            temp->print = &printCity;
            temp->destroy = &destroyCity;

            temp++;
        }
    }
    return citiesList;

}

