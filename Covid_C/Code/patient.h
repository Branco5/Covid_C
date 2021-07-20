/**
 * @file patient.h
 * @brief Definition of Patient struct.
 *
 * Defines the type Patient and associated operations.
 *
 * @author Bernardo Mota & Tiago Branco
 * @bug No known bugs.
 */

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "date.h"
#include "patient.h"

/**
 * @brief Represents a monitored patient
 *
 */
typedef struct patient
{
    long int id;
    char sex[6]; // {“male”, “female”}
    int birthYear;
    char country[40]; //birth country
    char region[40];
    char infectionReason[100];
    long int infectedBy; // id of the infected patient
    Date confirmedDate;
    Date releasedDate;
    Date deceasedDate;
    char status[10]; // {“isolated, “released”, “deceased”}
} Patient;

/**
 * @brief Creates a new instance of Patient
 *
 * @param id unique numerical id of patient
 * @param sex male or female
 * @param birthYear birthyear of patient
 * @param country country of residence
 * @param region region of residence
 * @param infectionReason how patient contracted disease
 * @param infectedBy patient who transmitted disease
 * @param confirmedDate day in which infection was confirmed
 * @param releasedDate day in which patient was released
 * @param deceasedDate day in which patient died
 * @param status current quarantine status
 * @return Patient
 */
Patient patientCreate(long int id, char sex[6], int birthYear, char country[40], char region[40], char infectionReason[100],
                      long int infectedBy, Date confirmedDate, Date releasedDate, Date deceasedDate, char status[10]);

/**
 * @brief Prints out patient information
 *
 * @param pat Patient to print out
 */
void patientPrint(Patient pat);

/**
 * @brief Calculates and returns age of patient
 *
 * @param p instance of Patient
 * @return int age of Patient
 */
int patientGetAge(Patient p);

/**
 * @brief Calculates and returns the number of days between the confirmed date of infection and the date of a new status
 *
 * If patient has no new status, the difference between today and the day of infection is returned
 *
 * @param p Patient
 * @return int days between infection date and change of status/today
 */
int patientGetIllnessDays(Patient p);
