#include <time.h>
#include "patient.h"

#include "utils.h"

Patient patientCreate(long int id, char sex[6], int birthYear, char country[40], char region[40], char infectionReason[100],
                      long int infectedBy, Date confirmedDate, Date releasedDate, Date deceasedDate, char status[10])
{
    Patient pat;

    pat.id = id;
    strcpy(pat.sex, sex);
    pat.birthYear = birthYear;
    strcpy(pat.country, country);
    strcpy(pat.region, region);
    strcpy(pat.infectionReason, infectionReason);
    pat.infectedBy = infectedBy;
    pat.confirmedDate = confirmedDate;
    pat.releasedDate = releasedDate;
    pat.deceasedDate = deceasedDate;
    strcpy(pat.status, status);

    return pat;
}

void patientPrint(Patient pat)
{
    printf("ID: %ld \n SEX: %s \n Country/Region: %s/%s \n Infection Reason: %s \n Infected by: %ld \n Birth Year: %d \n Status: %s ",
           pat.id, pat.sex, pat.country, pat.region, pat.infectionReason, pat.infectedBy, pat.birthYear, pat.status);
    datePrint(pat.confirmedDate);
    datePrint(pat.releasedDate);
    datePrint(pat.deceasedDate);
    printf("\n\n");
}

int patientGetAge(Patient p)
{
    if (p.birthYear == -1)
    {
        return -1;
    }
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return (tm.tm_year + 1900 - p.birthYear);
}

int patientGetIllnessDays(Patient p)
{
    int days = -1;

    if (equalsStringIgnoreCase(p.status, "isolated"))
    {
        Date today = dateToday();
        days = dateDaysBetween(p.confirmedDate, today);
    }
    else if (equalsStringIgnoreCase(p.status, "released"))
    {
        days = dateDaysBetween(p.confirmedDate, p.releasedDate);
    }
    else if (equalsStringIgnoreCase(p.status, "deceased"))
    {
        days = dateDaysBetween(p.confirmedDate, p.deceasedDate);
    }
    if (days < 1)
    {
        return -1;
    }
}

