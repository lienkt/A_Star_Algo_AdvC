/**
 * AStarAlgo.h
 * Author: Thi Lien KIM
 */

#ifndef __ASTARALGO_H
#define __ASTARALGO_H

#include <stdlib.h>
#include "status.h"
#include "List.h"

#include "City.h"

typedef int compSuccessor(void* s1, void* s2);
typedef void prSuccessor(void* s);
typedef int compCity(void* s1, void* s2);
typedef void prCity(void* s);

/**
 * aStar
 * @param city list
 * @param start city
 * @param goal city
 */
int aStar(List* cityList, int start, int goal, List * result);

/**
 * Update g and h of city list
 * @param 1 city
 */
void updateGnH(void * c);

/**
 * find Shortest Path
 * @param city list
 */
int findPath(List* cityList, List* openList, List* closeList, List* result);

#endif