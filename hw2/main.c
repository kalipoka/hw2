
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include "airport.h"
#include "ex2.h"



#define MAX_LINE_SIZE 256
Result createAirport(); //define that the function exists
PFLIGHT findFlightNum(int); //define that the function exists
PRUNWAY findRunway(int); //define that the function exists


int isInt(char* s)
{
	/*check if string is number*/
	int isDigit = 0;
	unsigned int j = 0;
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
			if (findRunway(num) != NULL) { // if we have this runway number already
				fprintf(stderr, "%s execution failed.\n", pszCmd);
				continue;
			}
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
				// check if we have this runway at all
				PRUNWAY temp = findRunway(num);
				if (temp == NULL) {
					fprintf(stderr, "%s execution failed.\n", pszCmd);
					continue;
				}
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

					//// check if we have this flight already
					if (findFlightNum(num)!=NULL) {           
						fprintf(stderr, "%s execution failed.\n", pszCmd);
						continue;
					}
					//// check if we haveA legal Num
					if (num<1 || num>MAX_ID) {
						fprintf(stderr, "%s execution failed.\n", pszCmd);
						continue;
					}

					if (!strcmp(P2, "I"))
						flighttype = INTERNATIONAL;
					else
						if (!strcmp(P2, "D"))
							flighttype = DOMESTIC;
						else {
							fprintf(stderr, "%s execution failed.\n", pszCmd);
							continue;
						}

						if (isDst(P3) != 0) {
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
							// check if we succed in adding the flight 
							if (addFlightToAirport(num, flighttype, P3, emergency) != SUCCESS) {
								fprintf(stderr, "%s execution failed.\n", pszCmd);
								continue;
								}
							
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
						// check if there are flights is the runway - ottherwise - fail
						PRUNWAY temp = findRunway(num);
						if (getFlightNum(temp) <= 0) {
							fprintf(stderr, "%s execution failed.\n", pszCmd);
							continue;
						}
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



