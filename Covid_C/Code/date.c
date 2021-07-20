#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "date.h"
#include "utils.h"

Date dateCreate(int day, int month, int year)
{
    Date d;
    d.day = day;
    d.month = month;
    d.year = year;

    return d;
}

void datePrint(Date d)
{
    printf("| %d/%d/%d | ", d.day, d.month, d.year);
}

int dateDaysBetween(Date d1, Date d2)
{
    int d1InDays = (d1.year * 365.25) + (d1.month * 30.44) + d1.day;
    int d2InDays = (d2.year * 365.25) + (d2.month * 30.44) + d2.day;

    int days = d2InDays - d1InDays;

    return days;
}

Date dateToday()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    Date d = dateCreate(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    return d;
}

Date datePrevious(Date d)
{
    Date prev;
    if (d.day > 1)
    {
        prev.day = d.day - 1;
        prev.month = d.month;
        prev.year = d.year;
    }
    else if (d.month > 1)
    {
        int daysInMonths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (d.year % 4 == 0)
            daysInMonths[1] = 29;
        prev.month = d.month - 1;
        prev.day = daysInMonths[prev.month - 1];
        prev.year = d.year;
    }
    else if (d.year > 1)
    {
        prev.year = d.year - 1;
        prev.month = 12;
        prev.day = 31;
    }
    else
    {
        prev = dateCreate(0, 0, 0);
    }
    return prev;
}