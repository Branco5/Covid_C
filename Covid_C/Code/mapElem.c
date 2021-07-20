/**
 * @file mapElem.c
 * @brief Implements operations for types MapKey and MapValue.
 *
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#include "mapElem.h"
#include <stdio.h>

void mapKeyPrint(MapKey key)
{
	printf("%s \n", key.name);
}

void mapValuePrint(MapValue value)
{
	regionPrint(value);
}

bool mapKeyEquals(MapKey key1, MapKey key2)
{
	// in case of string keys:
	return (strcmp(key1.name, key2.name) == 0);
}