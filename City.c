/**
 * City.c
 * Author: Thi Lien KIM
 */

#include <stdio.h>
#include <string.h>
#include "City.h"
#include "List.h"

/** create new city */
City* newCity(char *name, int lat, int longi) {
	City *city;
    city = (City*) malloc(sizeof(City));
	if (!city) return 0;
    char *cityName = malloc(sizeof(strlen(name) + 1));
	city->name = cityName;
    strcpy(cityName, name);
	city->lat = lat;
	city->longi =longi;
	city->h = 0;
	city->g = 0;
	city->f = 0;
	city->successors = NULL;
	city->ptr = NULL;
	return city;
}

/**destroy the city by deallocating used memory (O(N)). */
void delCity(City *city) {
    city->name = NULL;
    city->lat = 0;
    city->longi = 0;
    city->g = 0;
    city->h = 0;
	city->f = 0;
    city->successors = NULL;
    city->ptr = NULL;
    free(city);
}

/** create new successor */
Successor* newSuccessor(char *name, int distance) {
    Successor *successor;
    successor = (Successor*) malloc(sizeof(Successor));
    if (!successor) return 0;
    char *successorName = malloc(sizeof(strlen(name) + 1));
    strcpy(successorName, name);
    successor->name = successorName;
    successor->distance = distance;
    return successor;
}