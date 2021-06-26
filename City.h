/**
 * City.h
 * Author: Thi Lien KIM
 */

#ifndef __City_H
#define __City_H

#include <stdlib.h>
#include "status.h"

/** A Successors list of a city */
typedef struct Successor {
    char *name;
    int distance;
} Successor;

/** A City */
typedef struct City {
    char *name;
    int g, h, f, lat, longi;
    struct List *successors;
    struct City *ptr;
} City;

/**
 * create new city
 * @param city name
 * @param latitude
 * @param longitude
 * @return a city
 * @return 0 otherwise
 */
City* newCity(char *name, int lat, int longi);

/**
 * destroy the city by deallocating used memory (O(N)).
 * @param l the city to destroy */
void delCity(City *city);

/**
 * create new Successor
 * @param name of Successor
 * @param distance from the city to this Successor
 * @return a Successor
 * @return 0 otherwise
 */
Successor* newSuccessor(char *name, int distance);

#endif
