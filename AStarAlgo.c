/**
 * AStarAlgo.c
 * Author: Thi Lien KIM
 */

#include <stdio.h>
#include <string.h>
#include "AStarAlgo.h"
#include "List.h"
//#include "List.c"
#include "City.h"
#include "status.h"

static Successor * si = NULL;
static City* startCity = NULL;
static City* goalCity = NULL;

/**
 * Function to compare two elements (strings) : based on strcmp
 * @param s1 the first string to compare
 * @param s2 the second string to compare
 * @return <0 if s1 is less than s2
 * @return 0 if s1 equals s2
 * @return >0 otherwise
 */ 
static int compSuccessor (void * s1, void * s2) {
	Successor* c1 = s1;
    Successor* c2 = s2;
	return strcasecmp(c1->name, c2->name);
}

/**
 * Function to display an element of the list
 * @param s the string to display
 */ 
static void prSuccessor(void * s) {
    Successor* c = s;
    printf("Successor: %s\n", c->name);
}

/**
 * Function to compare two elements (strings) : based on strcmp
 * @param s1 the first string to compare
 * @param s2 the second string to compare
 * @return <0 if s1 is less than s2
 * @return 0 if s1 equals s2
 * @return >0 otherwise
 */ 
static int compCity (void * s1, void * s2) {
	City* city1 = s1;
    City* city2 = s2;
	return strcasecmp(city1->name, city2->name);
}

/**
 * Function to display an element of the list
 * @param s the string to display
 */ 
static void prCity(void * s) {
    City* city = s;
    printf("City: %s\n", city->name);
    List * successors = city->successors;
    printf("Successors: %d\n", lengthList(successors));
    printf("\n");
	forEach(successors, prSuccessor);
    printf("\n");
}

/** Update g and h of city list */
void updateGnH(void * s) {
	City * tmp = s;
	if (tmp != startCity) {
		tmp->g = 3000;
		
	} else {
		tmp->g = 0;
	}
	if (tmp != goalCity) {
		// h = (abs(x1-x2) + abs(y1-y2))/4
		tmp->h = (abs(tmp->lat - goalCity->lat) 
				+ abs(tmp->longi - goalCity->longi))/4;
	} else {
		tmp->h = 0;
	}
}

/** compare current successor (si) in city list */
int compCityNameAndSi(void * c) {
    City *city = c;
    return strcasecmp(city->name, si->name) == 0;
}

/** find Shortest Path */
int findPath(List* cityList, List* openList, List* closeList, List* result) {
	City* currentCity = openList->head->val;
	City* minFCity = NULL;
	while (currentCity != goalCity) {
		if (lengthList(openList) > 0) {
			if (minFCity != NULL) {
				currentCity = minFCity;
			}
			printf("\naaaaaaaaaaaaaaaaa1");
			printf("\ncurrentCity 1111: %s", currentCity->name);
			prCity(currentCity);
			// remove from OPEN the vertex with minimal f
			remFromList(openList, currentCity);
				//remFromListAt(openList, 1, &currentCity);
			// add current city (n) to CLOSED
			addList(closeList, currentCity);
			// if n is goal
			if (currentCity == goalCity) {
				printf("\naaaaaaaaaaaaaaaaa2");
				while (currentCity->ptr) {
					// use pointer chain to retieve the solution path
					addList(result, currentCity);
					currentCity = currentCity->ptr;
				}
				addList(result, currentCity);
				return 1;
			}
			
    		Node * tmpSi = currentCity->successors->head;
			// For each successor (si) of n:
			while (tmpSi) {
				si = tmpSi->val;
				// find current successor (si) in city list
				City * siCity = firstThat(cityList, compCityNameAndSi);
				if (minFCity == NULL || minFCity->f > siCity->f) {
					minFCity = siCity;
				}
				
				int gc = currentCity->g + si->distance;
				// if si is in OPEN or CLOSED and gc > g(si)
				if ((isInList(openList, siCity) || isInList(closeList, siCity))
					&& gc > siCity->g) {
					 // skip to next successor
					tmpSi = tmpSi->next;
					continue;
				}
				// remove si in OPEN and CLOSED
				if (isInList(openList, siCity)) {
					remFromList(openList, siCity);
				}
				if (isInList(closeList, siCity)) {
					remFromList(closeList, siCity);
				}
				// update g(si), f(si) and back-path pointer
				siCity->g = gc;
				siCity->f = siCity->g + siCity->h;
				siCity->ptr = currentCity;
				printf("\naaaaaaaaaaaaaaaaa1");
				printf("\ncurrentneibor222: %s", siCity->name);
				printf("\ncurrentneibor222 g: %s", siCity->g);
				printf("\ncurrentneibor222 h: %s", siCity->h);
				printf("\ncurrentneibor222 f: %s", siCity->f);
				// insert si in OPEN
				addList(openList, siCity);
				
				// move to next successor
				tmpSi = tmpSi->next;
			}
			return 1;
		} else {
			return 0;
		}
	}
}

/** A Star Algo */
int aStar(List* cityList, int start, int goal, List * result) {
 	List* openList;
 	List* closeList;
    nthInList (cityList, start, &startCity);
    nthInList (cityList, goal, &goalCity);
    if (startCity == NULL || goalCity == NULL) {
        printf("\nInvalid input cities!");
		return 0;
    }
	printf("\nstartCity: %s", startCity->name);
	printf("\ngoalCity: %s", goalCity->name);
	// OPEN
	openList = newList(compCity, prCity);
	// CLOSE
	closeList = newList(compCity, prCity);
	// Place n0 in OPEN 
    addList(openList, startCity);
	// Update g and h of city list after having startCity and goalCity:
    forEach(cityList, updateGnH);
	
    findPath(cityList, openList, closeList, result);
	delList(openList);
	delList(closeList);
	return 1;
}
