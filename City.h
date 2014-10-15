/* 
 * File:   City.h
 * Author: bamasyali
 *
 * Created on October 24, 2013, 8:56 PM
 */

#ifndef LIBS
#define LIBS 1
#include <stdio.h>
#include <stdlib.h>
#endif

typedef struct CityStruct {
    int id;
    double lat;
    double lng;

    void (*destroy)(struct CityStruct*);
    void (*print)(struct CityStruct*);

} City;

City * initCity();

City * readCitiesFromFile(FILE * file, int cityNumber);

inline double calculateDistance(City* city1, City* city2);

double calculateDistanceById(City * cities, int city1, int city2);
