#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "region.h"

Region regionCreate(char name[40], char capital[40], int population, float area)
{
    Region r;
    strcpy(r.name, name);
    strcpy(r.capital, capital);
    r.population = population;
    r.area = area;
    return r;
}

void regionPrint(Region r)
{
    printf("NAME: %s\nCAPITAL: %s\nPOPULATION: %d\nAREA: %f\n", r.name, r.capital, r.population, r.area);
}