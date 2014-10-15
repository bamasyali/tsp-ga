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

    double (*calculateDistance)(struct CityStruct*, struct CityStruct*);
    double (*calculateDistanceById)(struct CityStruct*, int, int);
    void (*print)(struct CityStruct*);
    void (*destroy)(struct CityStruct*);
} City;

City * initCity();

City * readCitiesFromFile(FILE * file, int cityNumber);
