/**
 * @file main.c
 * @brief Program's point of entry and main loop.
 *
 * Implements main features of the program and user interface.
 *
 * @author Bernardo Mota & Tiago Branco
 * @bug No known bugs.
 */

/* PROJETO  ATAD 2019-20
* Identificacao dos Alunos:
*
*      Numero: 190221009 | Nome: Bernardo Mota
*      Numero: 190221032 | Nome: Tiago Branco
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "utils.h"
#include "ctype.h"
#include "map.h"
#include "patient.h"

typedef char String[255];

/* definicao de prototipos de funcoes, definidas depois do main() */

/**
 * @brief Shows available commands to the user
 *
 */
void printCommandsMenu();

/**
 * @brief Imports data from file if user input matches its name
 *
 * @param mapRegions pointer to map variable to hold information extracted from file
 */
void importRegions(PtMap *mapRegions);

/**
 * @brief Imports data from file if user input matches its name
 *
 * @param listPatients pointer to list variable to hold information extracted from file
 */
void importPatients(PtList *listPatients);

/**
 * @brief Shows average age of patients by status
 *
 * @param listPatients pointer to list to extract information from
 */
void showAverage(PtList listPatients);

/**
 * @brief Presents information regarding requested patient and, if known, others in the same chain of infections
 *
 * @param listPatients pointer to list to extract information from
 */
void follow(PtList listPatients);

/**
 * @brief Shows percentage of patients by sex.
 *
 * @param listPatients pointer to list to extract information from
 */
void showSex(PtList listPatients);

/**
 * @brief Presents information regarding requested patient
 *
 * @param listPatients pointer to list to extract information from
 */
void showPatient(PtList listPatients);

/**
 * @brief Presents information regarding the top 5 patients that took the longest to recover
 *
 * @param listPatients pointer to list to extract information from
 */
void showTop5(PtList listPatients);

/**
 * @brief Prints detailed patient information in a vertical format
 *
 * @param p instance of Patient to print
 */
void printPatientLong(Patient p);

/**
 * @brief Prints patient information in a horizontal format
 *
 * @param p instance of Patient to print
 */
void printPatientShort(Patient p);

/**
 * @brief Shows oldest patients by sex
 *
 * @param listPatients pointer to list to extract information from
 */
void showOldest(PtList listPatients);

/**
 * @brief Shows rate of new infected and dead patients on a specified date compared to the day before
 *
 * @param listPatients pointer to list to extract information from
 */
void showGrowth(PtList listPatients);

/**
 * @brief Erases the records in the specified lists
 *
 * @param listPatients pointer to list of patients
 * @param mapRegions pointer to map of regions
 */
void clear(PtList listPatients, PtMap mapRegions);

/**
 * @brief Shows numbers of patients by status and age in a matrix format
 *
 * @param listPatients pointer to list to extract information from
 */
void showMatrix(PtList listPatients);

/**
 * @brief Shows information about each monitored region with the respective number of isolated patients
 *
 * @param listPatients pointer to list of patients
 * @param mapRegions pointer to map of regions
 */
void showRegions(PtList listPatients, PtMap mapRegions);

/**
 * @brief Creates a text file with statistics regarding mortality and infection rates by region
 *
 * @param listPatients pointer to list of patients
 * @param mapRegions pointer to map of regions
 */
void report(PtList listPatients, PtMap mapRegions);
//...

/*
* Descrição do Programa
*/
int main(int argc, char **argv)
{

	/* declaracao de variaveis */
	PtList listPatients = listCreate(10);
	PtMap mapRegions = mapCreate(10);

	/* interpretador de comandos */
	String command;
	int quit = 0;

	setlocale(LC_ALL, "PT");
	while (!quit)
	{

		printCommandsMenu();
		fgets(command, sizeof(command), stdin);
		/* descartar 'newline'. Utilizar esta técnica sempre que for lida uma
		* string para ser utilizada, e.g., nome de ficheiro, chave, etc.. */
		command[strlen(command) - 1] = '\0';

		if (equalsStringIgnoreCase(command, "QUIT"))
		{

			quit = 1; /* vai provocar a saída do interpretador */
		}
		else if (equalsStringIgnoreCase(command, "LOADP"))
		{
			importPatients(&listPatients);
		}
		else if (equalsStringIgnoreCase(command, "LOADR"))
		{
			importRegions(&mapRegions);
			int size;
			mapSize(mapRegions, &size);
			printf("map size after import = %d\n", size);
		}
		else if (equalsStringIgnoreCase(command, "CLEAR"))
		{
			clear(listPatients, mapRegions);
		}
		else if (equalsStringIgnoreCase(command, "AVERAGE"))
		{
			showAverage(listPatients);
		}
		else if (equalsStringIgnoreCase(command, "FOLLOW"))
		{
			follow(listPatients);
		}
		else if (equalsStringIgnoreCase(command, "SEX"))
		{
			showSex(listPatients);
		}
		else if (equalsStringIgnoreCase(command, "SHOW"))
		{
			showPatient(listPatients);
		}
		else if (equalsStringIgnoreCase(command, "TOP5"))
		{
			showTop5(listPatients);
		}
		else if (equalsStringIgnoreCase(command, "OLDEST"))
		{
			showOldest(listPatients);
		}
		else if (equalsStringIgnoreCase(command, "GROWTH"))
		{
			showGrowth(listPatients);
		}
		else if (equalsStringIgnoreCase(command, "MATRIX"))
		{
			showMatrix(listPatients);
		}
		else if (equalsStringIgnoreCase(command, "REGIONS"))
		{
			showRegions(listPatients, mapRegions);
		}
		else if (equalsStringIgnoreCase(command, "REPORT"))
		{
			report(listPatients, mapRegions);
		}
		else
		{
			printf("%s : Comando não encontrado.\n", command);
		}
	}

	/* libertar memória e apresentar mensagem de saída. */
	listDestroy(&listPatients);
	mapDestroy(&mapRegions);

	return (EXIT_SUCCESS);
}

void printCommandsMenu()
{
	printf("\n===================================================================================");
	printf("\n                          PROJECT: COVID-19                    ");
	printf("\n===================================================================================");
	printf("\nA. Base Commands (LOADP, LOADR, CLEAR).");
	printf("\nB. Simple Indicators and searchs (AVERAGE, FOLLOW, MATRIX, OLDEST, GROWTH, SEX, SHOW, TOP5).");
	printf("\nC. Advanced indicator (REGIONS, REPORT)");
	printf("\nD. Exit (QUIT)\n\n");
	printf("COMMAND> ");
}

void importPatients(PtList *listPatients)
{
	char input[20];
	printf("Insira nome de um ficheiro de pacientes> ");

	fgets(input, sizeof(input), stdin);
	input[strlen(input) - 1] = '\0';

	importPatientsFromFile(input, listPatients);
}

void importRegions(PtMap *mapRegions)
{
	char input[20];
	printf("Insira nome de um ficheiro de regiões> ");

	fgets(input, sizeof(input), stdin);
	input[strlen(input) - 1] = '\0';

	importRegionsFromFile(input, mapRegions);
}

void showAverage(PtList listPatients)
{
	int total;
	listSize(listPatients, &total);

	if (total > 0)
	{
		PtList deceasedPatients = getPatientsByStatus(listPatients, "deceased");
		PtList releasedPatients = getPatientsByStatus(listPatients, "released");
		PtList isolatedPatients = getPatientsByStatus(listPatients, "isolated");

		float avgd = getAverageAge(deceasedPatients);
		float avgr = getAverageAge(releasedPatients);
		float avgi = getAverageAge(isolatedPatients);

		listDestroy(&deceasedPatients);
		listDestroy(&releasedPatients);
		listDestroy(&isolatedPatients);

		printf("Average Age for deceased patients: <%f>\n", avgd);
		printf("Average Age for released patients: <%f>\n", avgr);
		printf("Average Age for isolated patients: <%f>\n", avgi);
	}
	else
	{
		printf("No patient data available...\n");
	}
}

void showSex(PtList listPatients)
{
	int total;
	listSize(listPatients, &total);

	if (total > 0)
	{
		PtList malePatients = getPatientsBySex(listPatients, "male");
		PtList femalePatients = getPatientsBySex(listPatients, "female");

		int male;
		int female;

		listSize(malePatients, &male);
		listSize(femalePatients, &female);

		listDestroy(&malePatients);
		listDestroy(&femalePatients);

		float percentFem = (((float)female / (float)total) * 100);
		float percentMale = (((float)male / (float)total) * 100);
		float percentUnknown = 100 - (percentFem + percentMale);

		printf("Percentage of Females: %04.2f%%\n", percentFem);
		printf("Percentage of Males: %04.2f%%\n", percentMale);
		printf("Percentage of unknown: %04.2f%%\n", percentUnknown);
		printf("Total of patients: %d\n", total);
	}
	else
	{
		printf("No patient data available...\n");
	}
}

void follow(PtList listPatients)
{
	char input[20];
	printf("Insira ID de um paciente> ");

	fgets(input, sizeof(input), stdin);
	input[strlen(input) - 1] = '\0';

	long int id = strtol(input, NULL, 10);

	int success;

	Patient p;
	success = getPatientById(listPatients, id, &p);

	if (success == 0)
	{
		printf("Paciente não encontrado.\n");
		return;
	}
	printf("Following Patient: ");
	printPatientShort(p);

	while (p.infectedBy != -1)
	{
		success = getPatientById(listPatients, p.infectedBy, &p);
		if (success == 0)
		{
			break;
		}
		printf("contaminated by: ");
		printPatientShort(p);
	}
	printf("contaminated by: unknown\n");
}

void showPatient(PtList listPatients)
{
	char input[20];
	printf("Insira ID de um paciente> ");

	fgets(input, sizeof(input), stdin);
	input[strlen(input) - 1] = '\0';

	long int id = strtol(input, NULL, 10);

	int success;

	Patient p;
	success = getPatientById(listPatients, id, &p);

	if (success == 0)
	{
		printf("Paciente não encontrado.\n");
		return;
	}

	printPatientLong(p);
}

void printPatientLong(Patient p)
{
	printf("ID: %ld\n", p.id);
	printf("SEX: %s\n", p.sex);
	int age = patientGetAge(p);
	if (age != -1)
	{
		printf("AGE: %d\n", age);
	}
	else
	{
		printf("AGE: unknown\n");
	}
	printf("COUNTRY/REGION: %s/%s\n", p.country, p.region);
	printf("INFECTION REASON: %s\n", p.infectionReason);
	printf("STATE: %s\n", p.status);

	int illnessDays = patientGetIllnessDays(p);
	if (illnessDays != -1)
	{
		printf("NUMBER OF DAYS WITH ILLNESS: %d\n", patientGetIllnessDays(p));
	}
	else
	{
		printf("NUMBER OF DAYS WITH ILLNESS: unknown\n");
	}
}

void printPatientShort(Patient p)
{
	printf("ID: %ld, SEX: %s, AGE: %d, COUNTRY/REGION: %s/%s, STATE: %s\n", p.id, p.sex, patientGetAge(p), p.country, p.region, p.status);
}

void showTop5(PtList listPatients)
{
	int size;
	listSize(listPatients, &size);

	Patient top5[5];
	int count = 0;

	for (int i = 0; i < size; ++i)
	{
		Patient p1;
		listGet(listPatients, i, &p1);
		if (strcmp(p1.status, "released") != 0)
			continue;
		int illnessDays = patientGetIllnessDays(p1);

		if (illnessDays > 0)
		{
			bool inserted = false;
			for (int j = 0; j < count; ++j)
			{
				int illnessDays2 = patientGetIllnessDays(top5[j]);

				if ((illnessDays > illnessDays2) || (illnessDays == illnessDays2 && patientGetAge(p1) > patientGetAge(top5[j])))
				{
					for (int k = 4; k > j; --k)
					{
						top5[k] = top5[k - 1];
					}
					top5[j] = p1;
					inserted = true;
					break;
				}
			}
			if (!inserted && count < 5)
			{
				top5[count] = p1;
				inserted = true;
			}
			if (inserted && count < 5)
				++count;
		}
	}

	printf("TOP 5: \n\n");
	for (int i = 0; i < count; ++i)
	{
		printPatientLong(top5[i]);
		printf("\n");
	}
}

void showOldest(PtList listPatients)
{

	PtList femalePatients = getPatientsBySex(listPatients, "female");
	PtList malePatients = getPatientsBySex(listPatients, "male");

	sortPatientsByOldest(femalePatients);
	sortPatientsByOldest(malePatients);

	int fSize, mSize;
	listSize(femalePatients, &fSize);
	listSize(malePatients, &mSize);

	int maxBirthYear = -1;

	printf("FEMALES:\n");
	for (int i = 0; i < fSize; ++i)
	{

		Patient p;
		listGet(femalePatients, i, &p);
		if (p.birthYear == -1)
			break;

		if (maxBirthYear == -1)
			maxBirthYear = p.birthYear;

		if (p.birthYear != maxBirthYear)
			break;

		printf("%d - ", i + 1);
		printPatientShort(p);
	}

	maxBirthYear = -1;

	printf("MALES:\n");
	for (int i = 0; i < mSize; ++i)
	{
		Patient p;
		listGet(malePatients, i, &p);
		if (p.birthYear == -1)
			break;

		if (maxBirthYear == -1)
			maxBirthYear = p.birthYear;

		if (p.birthYear != maxBirthYear)
			break;

		printf("%d - ", i + 1);
		printPatientShort(p);
	}

	listDestroy(&femalePatients);
	listDestroy(&malePatients);
}

void showGrowth(PtList listPatients)
{
	char input[20];
	printf("Insira data> ");

	fgets(input, sizeof(input), stdin);
	input[strlen(input) - 1] = '\0';

	Date d = stringToDate(input);

	if (d.day < 1 || d.day > 31 || d.month < 1 || d.month > 12 || d.year < 1)
	{
		printf("Data introduzida é inválida.\n");
		return;
	}

	Date prev = datePrevious(d);

	int deceasedAtDate = totalDeceasedAtDate(listPatients, d);
	int isolatedAtDate = totalIsolatedAtDate(listPatients, d);

	if (deceasedAtDate == 0 && isolatedAtDate == 0)
	{
		printf("There is no record for day ");
		datePrint(d);
		printf("\n");
		return;
	}

	int deceasedAtPrev = totalDeceasedAtDate(listPatients, prev);
	int isolatedAtPrev = totalIsolatedAtDate(listPatients, prev);

	if (deceasedAtPrev == 0 && isolatedAtPrev == 0)
	{
		printf("There is no record for day ");
		datePrint(prev);
		printf("\n");
		return;
	}

	printf("\nDate: ");
	datePrint(prev);
	printf("\nNumber of dead: %d\n", deceasedAtPrev);
	printf("Number of isolated: %d\n", isolatedAtPrev);

	printf("\nDate: ");
	datePrint(d);
	printf("\nNumber of dead: %d\n", deceasedAtDate);
	printf("Number of isolated: %d\n", isolatedAtDate);

	printf("\nRate of new dead: %f\n",
				 (float)(deceasedAtDate - deceasedAtPrev) / (float)(deceasedAtPrev));
	printf("Rate of new infected: %f\n",
				 (float)(isolatedAtDate - isolatedAtPrev) / (float)(isolatedAtPrev));
}

void clear(PtList listPatients, PtMap mapRegions)
{

	int numberPatients;
	listSize(listPatients, &numberPatients);

	int numberRegions;
	mapSize(mapRegions, &numberRegions);

	listClear(listPatients);
	mapClear(mapRegions);

	printf("%d records deleted from Patients\n", numberPatients);
	printf("%d records deleted from Regions\n", numberRegions);
}

void showMatrix(PtList listPatients)
{
	int totals[6][3] = {
			{0, 0, 0},
			{0, 0, 0},
			{0, 0, 0},
			{0, 0, 0},
			{0, 0, 0},
			{0, 0, 0},
	};

	int size;
	listSize(listPatients, &size);

	for (int i = 0; i < size; ++i)
	{
		Patient p;
		listGet(listPatients, i, &p);

		int coll, line;

		if (equalsStringIgnoreCase(p.status, "isolated"))
		{
			coll = 0;
		}
		else if (equalsStringIgnoreCase(p.status, "deceased"))
		{
			coll = 1;
		}
		else if (equalsStringIgnoreCase(p.status, "released"))
		{
			coll = 2;
		}
		else
		{
			continue;
		}

		int age = patientGetAge(p);

		if (age >= 0 && age <= 15)
		{
			line = 0;
		}
		else if (age >= 16 && age <= 30)
		{
			line = 1;
		}
		else if (age >= 31 && age <= 45)
		{
			line = 2;
		}
		else if (age >= 46 && age <= 60)
		{
			line = 3;
		}
		else if (age >= 61 && age <= 75)
		{
			line = 4;
		}
		else if (age >= 76)
		{
			line = 5;
		}
		else
		{
			continue;
		}

		++totals[line][coll];
	}

	printf("          | isolated | deceased | released |\n");
	printf(" [ 0-15]  | %8d | %8d | %8d |\n", totals[0][0], totals[0][1], totals[0][2]);
	printf(" [16-30]  | %8d | %8d | %8d |\n", totals[1][0], totals[1][1], totals[1][2]);
	printf(" [31-45]  | %8d | %8d | %8d |\n", totals[2][0], totals[2][1], totals[2][2]);
	printf(" [46-60]  | %8d | %8d | %8d |\n", totals[3][0], totals[3][1], totals[3][2]);
	printf(" [61-75]  | %8d | %8d | %8d |\n", totals[4][0], totals[4][1], totals[4][2]);
	printf(" [76...[  | %8d | %8d | %8d |\n", totals[5][0], totals[5][1], totals[5][2]);
}

void showRegions(PtList listPatients, PtMap mapRegions)
{
	int size;
	mapSize(mapRegions, &size);

	MapKey *keys = mapKeys(mapRegions);

	for (int i = 0; i < size - 1; ++i)
	{
		MapKey min = keys[i];
		int indexMin = i;
		for (int j = i + 1; j < size; ++j)
		{
			if (strcmp(min.name, keys[j].name) > 0)
			{
				min = keys[j];
				indexMin = j;
			}
		}
		MapKey swap = keys[i];
		keys[i] = min;
		keys[indexMin] = swap;
	}

	int *totalsIsolated = (int *)calloc(size, sizeof(int));

	int sizeP;
	listSize(listPatients, &sizeP);

	for (int i = 0; i < sizeP; ++i) //patients
	{
		Patient p;
		listGet(listPatients, i, &p);
		for (int j = 0; j < size; ++j) //regions
		{
			if (strcmp(p.region, keys[j].name) == 0)
			{
				if (strcmp(p.status, "isolated") == 0)
					totalsIsolated[j]++;
				break;
			}
		}
	}

	for (int i = 0; i < size; ++i)
	{
		if (totalsIsolated[i] > 0)
		{
			Region r;
			mapGet(mapRegions, keys[i], &r);
			regionPrint(r);
			printf("Number of patients isolated: %d\n\n", totalsIsolated[i]);
		}
	}

	free(totalsIsolated);
	free(keys);
}

void report(PtList listPatients, PtMap mapRegions)
{
	FILE *f;

	f = fopen("report.txt", "w+");

	int sizeP;
	listSize(listPatients, &sizeP);

	int sizeR;
	mapSize(mapRegions, &sizeR);

	MapKey *keys = mapKeys(mapRegions);

	int *casesCount = (int *)calloc(sizeR, sizeof(int));
	int *deathsCount = (int *)calloc(sizeR, sizeof(int));

	int totalDeaths = 0;

	for (int i = 0; i < sizeP; ++i)
	{
		Patient p;
		listGet(listPatients, i, &p);

		for (int j = 0; j < sizeR; ++j)
		{
			if (equalsStringIgnoreCase(p.region, keys[j].name))
			{
				++casesCount[j];
				if (equalsStringIgnoreCase(p.status, "deceased"))
				{
					++deathsCount[j];
					++totalDeaths;
				}
				break;
			}
		}
	}

	int totalPopulation = 0;
	for (int i = 0; i < sizeR; ++i)
	{
		Region r;
		mapGet(mapRegions, keys[i], &r);
		totalPopulation += r.population;
	}

	fprintf(f, "TOTAL:\n\tMortality: %f%%, Incident Rate: %f%%, Lethality: %f%%\n\n",
					(float)totalDeaths / totalPopulation * 10000,
					(float)sizeP / totalPopulation * 100,
					(float)totalDeaths / sizeP * 100);

	for (int i = 0; i < sizeR; ++i)
	{
		Region r;
		mapGet(mapRegions, keys[i], &r);
		if (casesCount[i] == 0 || r.population == 0)
		{
			fprintf(f, "%s:\n\t(no population data)\n\n", keys[i].name);
			continue;
		}
		fprintf(f, "%s:\n\tMortality: %f%%, Incident Rate: %f%%, Lethality: %f%%\n\n", keys[i].name,
						(float)deathsCount[i] / r.population * 10000,
						(float)casesCount[i] / r.population * 100,
						(float)deathsCount[i] / casesCount[i] * 100);
	}

	free(keys);
	free(casesCount);
	free(deathsCount);
	if (fclose(f) != 0)
	{
		printf("Report not created.\n");
		return;
	};
	printf("Report created successfully.\n");
}