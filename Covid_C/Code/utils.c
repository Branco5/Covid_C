#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int equalsStringIgnoreCase(char str1[], char str2[])
{

	return (strcasecmp(str1, str2) == 0);
}

int substring(char *src, char *dst, int start)
{
	for (int i = start; i < strlen(src); ++i)
	{
		if (src[i] == ';' || src[i] == '\r')
		{
			dst[i - start] = '\0';

			return i + 1;
		}
		dst[i - start] = src[i];
	}
}

void cleanUpPopulationString(char *string)
{
	int size = strlen(string);
	for (int i = 0; i < size; ++i)
	{
		if (string[i] == ',')
		{
			for (int j = i; j < size - 1; ++j)
			{
				string[j] = string[j + 1];
			}
			--size;
			--i;
		}
	}
	string[size] = '\0';
}

void cleanUpAreaString(char *string)
{
	int size = strlen(string);
	for (int i = 0; i < size; ++i)
	{
		if (string[i] == ',')
		{
			string[i] = '.';
			break;
		}
	}
}

Date stringToDate(char *string)
{

	//printf("DATE PASSED: %s\n", string);
	Date d;

	if (strlen(string) < 1)
	{
		d = dateCreate(0, 0, 0);
	}
	else
	{

		int day;
		int month;
		int year;

		int filled = sscanf(string, "%d/%d/%d", &day, &month, &year);

		if (filled == 3)
		{
			d = dateCreate(day, month, year);
		}
		else
		{
			d = dateCreate(0, 0, 0);
		}
	}

	return d;
}

Patient createPatientFromString(char *string)
{
	long int id;

	int birthYear;
	long int infectedBy;
	Date confirmedDate;
	Date releasedDate;
	Date deceasedDate;

	char params[11][100];
	int index = 0;

	for (int i = 0; i < 11; ++i)
	{
		index = substring(string, params[i], index);
	}

	if (strlen(params[0]) > 0)
		id = atol(params[0]);
	else
		id = -1;

	if (strlen(params[2]) > 0)
		birthYear = atoi(params[2]);
	else
		birthYear = -1;

	if (strlen(params[6]) > 0)
		infectedBy = atol(params[6]);
	else
		infectedBy = -1;

	confirmedDate = stringToDate(params[7]);
	releasedDate = stringToDate(params[8]);
	deceasedDate = stringToDate(params[9]);

	Patient p = patientCreate(id, params[1], birthYear, params[3], params[4], params[5],
														infectedBy, confirmedDate, releasedDate, deceasedDate, params[10]);

	return p;
}

Region createRegionFromString(char *string)
{
	char name[40];
	char capital[40];
	int population;
	float area;

	char params[4][100];
	int index = 0;

	for (int i = 0; i < 4; ++i)
	{
		index = substring(string, params[i], index);
	}

	cleanUpPopulationString(params[3]);
	cleanUpAreaString(params[2]);

	strcpy(name, params[0]);
	strcpy(capital, params[1]);
	population = atoi(params[3]);
	area = atof(params[2]);

	printf("name %s -> %s\n", params[0], name);
	printf("capital %s -> %s\n", params[1], capital);
	printf("population %s -> %d\n", params[3], population);
	printf("area %s -> %f\n\n", params[2], area);

	Region r = regionCreate(params[0], params[1], atoi(params[3]), atof(params[2]));

	return r;
}

void importPatientsFromFile(char *filename, PtList *listPatients)
{
	printf("------------------------\n");
	FILE *f;

	f = fopen(filename, "r");

	if (f == NULL)
	{
		printf("An error ocurred... It was not possible to open the file %s ...\n", filename);
		return;
	}

	char nextline[1024];

	int countPatients = 0;

	int size;
	listSize(*listPatients, &size);

	bool firstLine = true;

	while (fgets(nextline, sizeof(nextline), f))
	{
		if (strlen(nextline) < 1)
			continue;

		/*As the first line of the file contains the names of the fields it should be ignored*/
		if (firstLine)
		{
			firstLine = false;
			continue;
		}

		nextline[strlen(nextline) - 1] = '\0';

		Patient patient = createPatientFromString(nextline);

		int error_code = listAdd(*listPatients, size + countPatients, patient);

		if (error_code == LIST_FULL || error_code == LIST_INVALID_RANK ||
				error_code == LIST_NO_MEMORY || error_code == LIST_NULL)
		{
			printf("An error ocurred... Please try again... \n");
			return;
		}
		countPatients++;
	}
	printf("\n\n%d patient reports were read!\n\n", countPatients);
	fclose(f);
}

void importRegionsFromFile(char *filename, PtMap *mapRegions)
{
	printf("------------------------\n");
	FILE *f = NULL;

	f = fopen(filename, "r");

	if (f == NULL)
	{
		printf("An error ocurred... It was not possible to open the file %s ...\n", filename);
		return;
	}

	char nextline[1024];

	int countRegions = 0;

	bool firstLine = true;

	while (fgets(nextline, sizeof(nextline), f))
	{
		if (strlen(nextline) < 1)
			continue;

		/*As the first line of the file contains the names of the fields it should be ignored*/
		if (firstLine)
		{
			firstLine = false;
			continue;
		}

		Region region = createRegionFromString(nextline);

		RegionName key;
		strcpy(key.name, region.name);

		int error_code = mapPut(*mapRegions, key, region);

		if (error_code == MAP_NO_MEMORY || error_code == MAP_FULL)
		{
			printf("An error ocurred... Please try again... \n");
			return;
		}
		countRegions++;
	}

	printf("\n\n%d regions were read!\n\n", countRegions);
	fclose(f);
}

int getPatientById(PtList listPatients, long int patientId, Patient *patient)
{
	int size;
	listSize(listPatients, &size);

	for (int i = 0; i < size; ++i)
	{
		Patient p;
		listGet(listPatients, i, &p);
		if (p.id == patientId)
		{
			*patient = p;
			return 1;
		}
	}
	return 0;
}

PtList getPatientsByStatus(PtList list, char *status)
{
	PtList patientsByStatus = listCreate(10);

	int pbsSize;
	listSize(patientsByStatus, &pbsSize);

	int size;
	listSize(list, &size);

	for (int i = 0; i < size; i++)
	{
		ListElem pat;
		listGet(list, i, &pat);
		if (equalsStringIgnoreCase(pat.status, status))
		{
			listAdd(patientsByStatus, pbsSize, pat);
			listSize(patientsByStatus, &pbsSize);
		}
	}

	return patientsByStatus;
}

PtList getPatientsBySex(PtList list, char *sex)
{
	PtList patientsBySex = listCreate(10);

	int pbsSize;
	listSize(patientsBySex, &pbsSize);

	int size;
	listSize(list, &size);

	for (int i = 0; i < size; i++)
	{
		ListElem pat;
		listGet(list, i, &pat);
		if (equalsStringIgnoreCase(pat.sex, sex))
		{
			listAdd(patientsBySex, pbsSize, pat);
			listSize(patientsBySex, &pbsSize);
		}
	}

	return patientsBySex;
}

float getAverageAge(PtList list)
{
	int size;
	listSize(list, &size);

	int count = 0;
	int sum = 0;

	for (int i = 0; i < size; i++)
	{
		Patient pat;
		listGet(list, i, &pat);
		if (pat.birthYear > 0)
		{
			//sum += (2020 - pat.birthYear);
			sum += patientGetAge(pat);
			count++;
		}
	}
	if (count > 0)
		return ((float)sum / (float)count);
	else
		return -1;
}

void sortPatientsByOldest(PtList listPatients)
{
	int size;
	listSize(listPatients, &size);

	for (int i = 0; i < size - 1; ++i)
	{
		Patient min;
		listGet(listPatients, i, &min);

		int minIndex = i;
		for (int j = i + 1; j < size; ++j)
		{
			Patient p;
			listGet(listPatients, j, &p);
			if (min.birthYear == -1 || (p.birthYear != -1 && p.birthYear < min.birthYear))
			{
				min = p;
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			Patient prev;
			listSet(listPatients, i, min, &prev);
			listSet(listPatients, minIndex, prev, &min);
		}
	}
}

int totalIsolatedAtDate(PtList listPatients, Date d)
{
	int size;
	listSize(listPatients, &size);

	int count = 0;

	for (int i = 0; i < size; ++i)
	{
		Patient p;
		listGet(listPatients, i, &p);
		if (equalsStringIgnoreCase(p.status, "isolated"))

		{
			if (dateDaysBetween(p.confirmedDate, d) == 0)
			{
				++count;
			}
		}
	}

	return count;
}

int totalDeceasedAtDate(PtList listPatients, Date d)
{
	int size;
	listSize(listPatients, &size);

	int count = 0;

	for (int i = 0; i < size; ++i)
	{
		Patient p;
		listGet(listPatients, i, &p);
		if (equalsStringIgnoreCase(p.status, "deceased"))

		{
			if (dateDaysBetween(p.deceasedDate, d) == 0)
			{
				++count;
			}
		}
	}

	return count;
}