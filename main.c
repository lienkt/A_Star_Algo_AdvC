/**
 * main.c
 * Author: Thi Lien KIM
 */

#include <stdio.h>
#include <string.h>
#include "List.h"
#include "List.c"
#include "City.h"
#include "City.c"
//#include "AStarAlgo.h"
//#include "AStarAlgo.c"
//#include "status.h"

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
    printf("City lat: %d\n", city->lat);
    printf("City long: %d\n", city->longi);
    printf("City g: %d\n", city->g);
    printf("City h: %d\n", city->h);
    printf("City f: %d\n", city->f);
	if (city->ptr) printf("City ptr: %s\n", city->ptr->name);
    List * successors = city->successors;
    printf("Successors: %d\n", lengthList(successors));
	forEach(successors, prSuccessor);
    printf("\n");
}

/** Update g and h of city list */
void updateGnHnF(void * s) {
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
	tmp->f = tmp->g + tmp->h;
}

/** compare current successor (si) in city list */
int compCityNameAndSi(void * c) {
    City *city = c;
    return strcasecmp(city->name, si->name) == 0;
}

/** find Shortest Path */
int findPath(List* cityList, List* openList, List* closeList) {
	City* currentCity = openList->head->val;
	City* minFCity = NULL;
	int i = 1;
	while (currentCity != goalCity && i < 20) {
		if (lengthList(openList) > 0) {
			if (minFCity != NULL) {
				currentCity = minFCity;
			}
			// remove from OPEN the vertex with minimal f
			remFromList(openList, currentCity);
			// add current city (n) to CLOSED
			addList(closeList, currentCity);
			// if n is goal
			if (currentCity == goalCity) {
				List* res = newList(compCity, prCity);
				while (currentCity->ptr) {
					// use pointer chain to retieve the solution path
					addListAt(res, 1, currentCity);
					currentCity = currentCity->ptr;
				}
				addListAt(res, 1, currentCity);
				printf("\nThis is the shortest path: \n");
				printCitiesWithNumber(res);
				delList(res);
				return 1;
			}
			
    		Node * tmpSi = currentCity->successors->head;
			minFCity = NULL;
			// For each successor (si) of n:
			while (tmpSi) {
				si = tmpSi->val;
				// find current successor (si) in city list
				City * siCity = firstThat(cityList, compCityNameAndSi);
				
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
				if (minFCity == NULL || minFCity->f > siCity->f) {
					minFCity = siCity;
				}
				// insert si in OPEN
				addList(openList, siCity);
				
				// move to next successor
				tmpSi = tmpSi->next;
			}
		} else {
			return 0;
		}
		i++;
	}
	return 1;
}

/** A Star Algo */
int aStar(List* cityList, int start, int goal) {
 	List* openList;
 	List* closeList;
    nthInList (cityList, start, &startCity);
    nthInList (cityList, goal, &goalCity);
    if (startCity == NULL || goalCity == NULL) {
        printf("\nInvalid input cities!");
		return 0;
    }
	printf("\nStartCity: %s", startCity->name);
	printf("\nGoalCity: %s", goalCity->name);
	// OPEN
	openList = newList(compCity, prCity);
	// CLOSE
	closeList = newList(compCity, prCity);
	// Place n0 in OPEN 
    addList(openList, startCity);
	// Update g and h of city list after having startCity and goalCity:
    forEach(cityList, updateGnHnF);
	
    findPath(cityList, openList, closeList);
	delList(openList);
	delList(closeList);
	return 1;
}

void printCitiesWithNumber(List* cityList) {
    Node* tmp = cityList->head;
    for (int i = 1; i <= lengthList(cityList); i++) {
        City* city = tmp->val;
        printf("%d: %s\n", i, city->name);
        tmp = tmp->next;
    }
}

int main(int nWords, char* words[])
{
    
    char name[20];
    int lat, longi;
    int result;
    City* city = NULL;
    Successor* successor = NULL;
	List* cityList = newList(compCity, prCity);
	List* successorList = NULL;

    FILE *file;
    file = fopen("FRANCE.MAP", "r");
    if (!file) {
        perror("\nError opening file");
        exit(2);
    }
    // read FRANCE.MAP
    while ((result = fscanf(file, "%s%d%d", name, &lat, &longi))) {
        // a city line:
        if (result == 3) {
			successorList = newList(compSuccessor, prSuccessor);
            if (city) {
                addList(cityList, city);
            }
            city = newCity(name, lat, longi);
			city->successors = successorList;
        // a successor line:
        } else if (result == 2) {
            successor = newSuccessor(name, lat);
            if (successor) {
				addList(successorList,successor);
            }
        // end:
        } else if (result == EOF) {
            addList(cityList, city);
            break;
        }
    }
    fclose(file);

    int option = 0;
	while (option != 3)
	{
		printf("\nWelcome to my system!\n");
		printf("1. Show the city list.\n");
		printf("2. Find the shortest path between two cities.\n");
		printf("3. Exit.\n");
        printf("\n");
		printf("Please enter your option:");
		scanf("%d", &option);
		printf("\n");

		switch (option)
		{
			case 1:
				// Print cityList:
				printf("\nCities: %d\n", lengthList(cityList));
				forEach(cityList,prCity);
				break;
			case 2:
				// Find the shortest path between two cities:
				printCitiesWithNumber(cityList);
                int startcity, goalCity;
                printf("\nPlease enter start city number: ");
                scanf("%d", &startcity);
                printf("\nPlease enter goal city number: ");
                scanf("%d", &goalCity);
				aStar(cityList, startcity, goalCity);
				break;
			case 3:
				delCity(city);
				delList(cityList);
				delList(successorList);
				break;
		}
	}
}
