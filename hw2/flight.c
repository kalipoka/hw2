#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "flight.h"
#include "ex2.h"



PFLIGHT createFlight(int flight_num, FlightType flight_type, char destination[DEST_SIZE], BOOL emergency)
{
	PFLIGHT pFlight;
	printf("here 1\n");                 ///////////////////////////
	pFlight = (PFLIGHT)malloc(sizeof(FLIGHT));
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
	printf("here it is destroyed \n");                ///////////////////////////

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

	printf("Fligth %d %s %s %s\n", pFlight->flight_num, IsDomestic, pFlight->destination, IsEmergency);

	return SUCCESS;

}
