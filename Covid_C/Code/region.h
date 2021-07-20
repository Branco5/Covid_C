/**
 * @file region.h
 * @brief Definition of Region struct.
 *
 * Defines the type Region and associated operations.
 *
 * @author Bernardo Mota & Tiago Branco
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#pragma once

/**
 * @brief Represents a geographic region
 *
 */
typedef struct region
{
    char name[40];
    char capital[40];
    int population;
    float area;
} Region;

/**
 * @brief Prints out region details
 *
 * @param r Region object to print out
 */
void regionPrint(Region r);

/**
 * @brief Creates a new region
 *
 * @param name name of region
 * @param capital capital of region
 * @param population population of region
 * @param area area of region
 * @return Region instance
 */
Region regionCreate(char name[40], char capital[40], int population, float area);