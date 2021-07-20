/**
 * @file date.h
 * @brief Definition of Date struct.
 *
 * Defines the type Date and associated operations.
 *
 * @author Bernardo Mota & Tiago Branco
 * @bug No known bugs.
 */

#pragma once
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Defines a structure representative of a date
 *
 */
typedef struct date
{
    unsigned int day, month, year;
} Date;

/**
 * @brief Creates a new instance of Date
 *
 * @param day day of date
 * @param month month of date
 * @param year year of date
 * @return Date type
 */
Date dateCreate(int day, int month, int year);

/**
 * @brief Prints out a Date instance
 *
 * @param d Date to print
 */
void datePrint(Date d);

/**
 * @brief Returns amount of days between 2 specified dates
 *
 * @param d1 Date 1
 * @param d2 Date 2
 * @return int number of days between the 2 dates
 */
int dateDaysBetween(Date d1, Date d2);

/**
 * @brief Returns today's date according to geographic location
 *
 * @return Date
 */
Date dateToday();

/**
 * @brief Returns previous day of specified Date
 *
 * @param d Date specified Date
 * @return Date previous day
 */
Date datePrevious(Date d);