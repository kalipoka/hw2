#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include "airport.h"
#include "ex2.h"

#define MAX_LINE_SIZE 100


int isInt(char* s)
{
	/*check if string is number*/
	int isDigit = 0;
	int j = 0;
	while (j < strlen(s)) {
		if (isdigit(s[j]) != 0) return 1;
		j++;
	}
	return 0;
}


int main() {

	createAirport();

	char szLine[MAX_LINE_SIZE];
	char* delimiters = " \t\n";
	char* pszCmd;
	char* P1;
	char* P2;
	char* P3;
	char* P4;
	int num;
	BOOL emergency;
	FlightType flighttype;


	while (fgets(szLine, MAX_LINE_SIZE, stdin))
	{

		pszCmd = strtok(szLine, delimiters);
		P1 = strtok(NULL, delimiters);
		P2 = strtok(NULL, delimiters);
		P3 = strtok(NULL, delimiters);
		P4 = strtok(NULL, delimiters);

		if (!strcmp(pszCmd, "Insert")) // <runwayNumber> <runwayType>
		{

			if (P1 == NULL || P2 == NULL) {
				fprintf(stderr, "%s failed: not enough parameters.\n", pszCmd);
				continue;
			}
			if (!isInt(P1)) {
				fprintf(stderr, "%s execution failed.\n", pszCmd);
				continue;
			}
			num = atoi(P1);
			if (!strcmp(P2, "I"))
				flighttype = INTERNATIONAL;
			else
				if (!strcmp(P2, "D"))
					flighttype = DOMESTIC;
				else {
					fprintf(stderr, "%s execution failed.\n", pszCmd);//problem
					continue;
				}
				addRunway(num, flighttype);
				continue;
		}
		else
			if (!strcmp(pszCmd, "Remove")) //  <runwayNumber>
			{
				if (P1 == NULL)
				{
					fprintf(stderr, "%s failed: not enough parameters.\n", pszCmd);
					continue;
				}
				if (!isInt(P1))
				{
					fprintf(stderr, "%s execution failed.\n", pszCmd);
					continue;
				}
				num = atoi(P1);
				removeRunway(num);
				continue;
			}
			else
				if (!strcmp(pszCmd, "Add")) // <flightNumber> <flightType> <destenation> <emergency>
				{
					if (P1 == NULL || P2 == NULL || P3 == NULL || P4 == NULL) {
						fprintf(stderr, "%s failed: not enough parameters.\n", pszCmd);
						continue;
					}
					if (!isInt(P1)) {
						fprintf(stderr, "%s execution failed.\n", pszCmd);
						continue;
					}
					num = atoi(P1);

					if (!strcmp(P2, "I"))
						flighttype = INTERNATIONAL;
					else
						if (!strcmp(P2, "D"))
							flighttype = DOMESTIC;
						else {
							fprintf(stderr, "%s execution failed.\n", pszCmd);
							continue;
						}

						if (!strcmp(P4, "E"))
							emergency = TRUE;
						else
							if (!strcmp(P4, "R"))
								emergency = FALSE;
							else {
								fprintf(stderr, "%s execution failed.\n", pszCmd);
								continue;
							}

							addFlightToAirport(num, flighttype, P3, emergency);
							continue;
				}
				else
					if (!strcmp(pszCmd, "Depart")) // <runwayNumber>
					{
						if (P1 == NULL) {
							fprintf(stderr, "%s failed: not enough parameters.\n", pszCmd);
							continue;
						}

						if (!isInt(P1)) {
							fprintf(stderr, "%s execution failed.\n", pszCmd);
							continue;
						}
						num = atoi(P1);
						departFromRunway(num);
						continue;
					}
					else
						if (!strcmp(pszCmd, "Storm")) // <destenation>
						{
							if (P1 == NULL) {
								fprintf(stderr, "%s failed: not enough parameters.\n", pszCmd);
								continue;
							}
							stormAlert(P1);
							continue;
						}
						else
							if (!strcmp(pszCmd, "Print"))
							{
								printAirport();
								continue;
							}
							else
								if (!strcmp(pszCmd, "Exit"))
								{
									break;
								}
								else
								{
									fprintf(stderr, "Command not found.\n");
									continue;
								}
	}
	destroyAirport();
	return 0;
}



