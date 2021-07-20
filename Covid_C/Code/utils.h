/**
 * @file utils.h
 * @brief Helper functions for general data handling.
 *
 * @author Bernardo Mota & Tiago Branco
 * @bug No known bugs.
 */

#pragma once
#include "list.h"
#include "map.h"

#include "patient.h"

//char **split(char *string, int nFields, const char *delim); -- NOT USED

/**
 * @brief Compares 2 strings, ignoring case
 *
 * @param str1 string 1
 * @param str2 string 2
 * @return 0 if strings match
 */
int equalsStringIgnoreCase(char str1[], char str2[]);

/**
 * @brief Converts string object to a Date instance
 *
 * @param string string to convert
 * @return Date instance
 */
Date stringToDate(char *string);

/**
 * @brief Creates a Patient from a string object
 *
 * @param string string to convert
 * @return Patient instance
 */
Patient createPatientFromString(char *string);

/**
 * @brief Imports patient data from file and stores in a list structure
 *
 * @param filename file to extract data from
 * @param listPatients list structure to store data
 */
void importPatientsFromFile(char *filename, PtList *listPatients);

/**
 * @brief Imports region data from file and stores in a list structure
 *
 * @param filename file to extract data from
 * @param listPatients map structure to store data
 */
void importRegionsFromFile(char *filename, PtMap *mapRegions);

/**
 * @brief Gets a Patient by requested id
 *
 * @param listPatients [in] list to search patient
 * @param patientId [in] requested patient id
 * @param patient [out] Patient variable to store the requested patient information
 * @return int
 */
int getPatientById(PtList listPatients, long int patientId, Patient *patient);

/**
 * @brief Returns a pointer to a list of patients filtered by status
 *
 * @param list PtList to filter
 * @param status requested Patient status
 * @return PtList pointer to list of patients filtered by status
 */
PtList getPatientsByStatus(PtList list, char *status);

/**
 * @brief Returns the average age of patients in a list
 *
 * @param list pointer to list
 * @return float average age
 */
float getAverageAge(PtList list);

/**
 * @brief Returns a pointer to a list of patients filtered by sex
 *
 * @param list PtList to filter
 * @param sex requested sex of patients
 * @return PtList pointer to list of patients filtered by sex
 */
PtList getPatientsBySex(PtList list, char *sex);

/**
 * @brief Sorts patients from oldest to youngest
 *
 * @param listPatients pointer to list to sort
 */
void sortPatientsByOldest(PtList listPatients);

/**
 * @brief Returns total of patients isolated at specified date
 *
 * @param listPatients pointer to list of patients
 * @param d Date instance
 * @return int total of patients isolated at specified date
 */
int totalIsolatedAtDate(PtList listPatients, Date d);

/**
 * @brief Returns total of patients deceased at specified date
 *
 * @param listPatients pointer to list of patients
 * @param d Date instance
 * @return int total of patients deceased at specified date
 */
int totalDeceasedAtDate(PtList listPatients, Date d);