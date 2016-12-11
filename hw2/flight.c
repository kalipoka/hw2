#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "flight.h"
#include "ex2.h"



int isDst(char* s)
/*returns 0 if it is DST format*/
{
	int isDigit = 0;
	int j = 0;
	if (strlen(s) != DEST_SIZE)
		return 1;
	while (j < strlen(s)) {
		if (s[j] < 65 || s[j] >90) return 1;
		j++;
	}
	return 0;
}



PFLIGHT createFlight(int flight_num, FlightType flight_type, char destination[DEST_SIZE], BOOL emergency)
{
	if (((flight_type != DOMESTIC) && (flight_type != INTERNATIONAL)) || ((flight_num <= 0) && (flight_num > MAX_ID)) || ((emergency != FALSE) && (emergency != TRUE)))
		return NULL;
	if (isDst(destination) != 0)
		return NULL;
	
	PFLIGHT pFlight;
	pFlight = (PFLIGHT)malloc(sizeof(FLIGHT));
	if (pFlight == NULL)
		return NULL;
	if ((flight_num < 0) && (flight_num > MAX_ID)) return NULL;

	pFlight->flight_num = flight_num;
	pFlight->flight_type = flight_type;
	strcpy(pFlight->destination, destination);
	pFlight->emergency = emergency;
	return pFlight;

}


void destroyFlight(PFLIGHT pFlight)
{
	free(pFlight);
	pFlight = NULL;

}


Result printFlight(PFLIGHT pFlight)
{

	if (pFlight == NULL)
		return FAILURE;
	else
		char *IsEmergency;
	if (pFlight->emergency)
		IsEmergency = "E";    /* Emergency flight */
	else
		IsEmergency = "R";    /*Regulat flight */

	char *IsDomestic;
	if (pFlight->flight_type == DOMESTIC)
		IsDomestic = "D";    /* DOMESTIC flight */
	else
		IsDomestic = "I";

	printf("Flight %d %s %s %s\n", pFlight->flight_num, IsDomestic, pFlight->destination, IsEmergency);

	return SUCCESS;

}