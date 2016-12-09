#include <stdio.h>
#include <string.h>
#include "airport.h"


#define MAX_LINE_SIZE 100

int main() {
	char szLine[MAX_LINE_SIZE];
	char* delimiters = " \t\n";
	char* pszName;
	char* pszsur;
	char* pszYear;
	int year;
	while (fgets(szLine, MAX_LINE_SIZE, stdin)) {
		printf("> %s", szLine);
		pszName = strtok(szLine, delimiters);
		pszYear = strtok(NULL, delimiters);
		year = atoi(pszYear);
		/*if (pszName == NULL || pszYear == NULL)
		{
			fprintf(stderr, "Error: Not enough parameters\n");
		}

		if (year == 0)
		{
			fprintf(stderr, "Error: Invalid year\n");
		}*/
		printf("%s %s is %d years old.\n", pszName, pszsur, 1992-year);
	}
	return 0;
}



//
//int main() {
//	char szLine[MAX_LINE_SIZE];
//	char* delimiters = " ";
//	char* pszCommand;
//	char* P1;
//	char* P2;
//	char* P3;
//	char* P4;
//
//	while (fgets(szLine, MAX_LINE_SIZE, stdin)) {
//		//printf("> %s", szLine);
//		pszCommand = strtok(szLine, delimiters);
//
//		if (strcmp(pszCommand, "Insert")
//		{
//
//		}
//		else
//			if (strcmp(pszCommand, "Remove") {
//			}
//			else
//				if (strcmp(pszCommand, "Add") {
//
//
//				else
//					if (strcmp(pszCommand, "Depart") {
//
//					}
//					else
//						if (strcmp(pszCommand, "Storm") {
//						}
//						else
//							if (strcmp(pszCommand, "Print") {
//							}
//							else
//								if (strcmp(pszCommand, "Exit");
//
//		pszYear = strtok(NULL, delimiters);
//		
//		if (pszName == NULL || pszYear == NULL)
//		{
//			fprintf(stderr, "Error: Not enough parameters\n");
//		}
//		year = atoi(pszYear);
//		if (year == 0)
//		{
//			fprintf(stderr, "Error: Invalid year\n");
//		}
//		printf("%s is %d years old.\n", pszName, year);
//	}
//	return 0;
//}