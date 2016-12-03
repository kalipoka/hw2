#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "flight.h"
#include "ex2.h"


int size_of_flight;
size_of_flight = sizeof(PFLIGHT);

PFLIGHT createFlight(int flight_num, FlightType flight_type, char destination[DEST_SIZE], BOOL emergency)
{
	PFLIGHT pFlight;
	printf("here 1\n");                 ///////////////////////////
	pFlight = (PFLIGHT)malloc(size_of_flight);
	printf("here 2\n");                ///////////////////////////
	if (pFlight == NULL)
		return NULL;
	printf("here 3\n");                ///////////////////////////
	pFlight->flight_num = flight_num;
	printf("here 4\n");                ///////////////////////////
	pFlight->flight_type = flight_type;
	printf("here 5\n");                ///////////////////////////
	strcpy(pFlight->destination, destination);
	printf("here 6\n");                ///////////////////////////
	pFlight->emergency = emergency;
	printf("here 7\n");                ///////////////////////////
	return pFlight;
}


void destroyFlight(PFLIGHT pFlight)
{
	free(pFlight);
	pFlight = NULL;
	printf("here 8\n");                ///////////////////////////

}


Result printFlight(PFLIGHT pFlight)
{
	
	if (pFlight == NULL)
		return FAILURE;

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

	printf("Fligth %d %s %s %s\n", pFlight->flight_num, IsDomestic, pFlight->destination, IsEmergency);

	return SUCCESS;

}
