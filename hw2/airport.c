#include "airport.h"

/*Globals*/
static PAIRPORT PAirport;


///helper functions
PFLIGHT findFlightNum(int flightNum)
{
	PRUNWAY_ELEM iRunways = PAirport->head->pNext;
	PFLIGHT_ELEM iFlights = iRunways->data->Lflight->head->pNext;

	while (!iRunways) {
		while (!iFlights)
		{
			if (isFlightExists(iRunways->data, flightNum) == TRUE)
				return iFlights->data;
			iFlights = iFlights->pNext;
		}
		iRunways = iRunways->pNext;
	}
	return NULL;
}

BOOL findRunway(int rwN) /* rwN = runway Number*/
{
	PRUNWAY_ELEM tmp = PAirport->head;
	while (tmp != NULL)
		if (tmp->data->runway_num == rwN)
			return TRUE;
		else
			tmp = tmp->pNext;
	/* if we got here, it means that the runway was not found */
	return FALSE;
}


Result addRunway(int Runway_num, FlightType Runway_type)
{
	/* chech is the number is legal*/
	if ((Runway_num < 0) && (Runway_num > MAX_ID))
		return FAILURE;
	if (findRunway(Runway_num) == TRUE)
	/* element already exist in the set*/
		return FAILURE;

	PRUNWAY_ELEM tmp;
	if (PAirport == NULL)
		return FAILURE;
	tmp = (PRUNWAY_ELEM)malloc(sizeof(RUNWAY_ELEM));
	/* check memory allocation*/
	if (!tmp) return FALSE;

	tmp->data = create_runway(Runway_num, Runway_type);

	tmp->pNext = PAirport->head;
	/* update the head */
	PAirport->head = tmp;
	return SUCCESS;
}
	

	

/*
Result removeRunway(int Runwaynum)
{
	PRUNWAY_ELEM currentR = PAirport->head->pNext;
	PRUNWAY_ELEM prevR = PAirport->head;
	while (!currentR)
	{
		if (currentR->data->runway_num == Runwaynum)
		{
			prevR->pNext = currentR->pNext;
			destroyRunway(currentR->data);
			free(currentR); //////CHECK IF IS CORRENLANCE AS IN ADDRUNWAY
		}
		prevR = currentR;
		currentR = currentR->pNext;
	}
}


Result addFlightToAirport(int flight_num, FlightType flight_type, char destination[DEST_SIZE], BOOL emergency)
{

	PRUNWAY_ELEM iRunways = PAirport->head->pNext;
	PRUNWAY Choosen_Runway;
	PFLIGHT new_flight = createFlight(flight_num, flight_type, destination, emergency);
	if (!new_flight)
		return FAILURE;

	Choosen_Runway->Lflight->size = 0;
	Choosen_Runway->runway_num = 999999;
	
	while (!iRunways)
	{
		if (iRunways->data->type == flight_type)
			if (isFlightExists(iRunways, flight_num) == FALSE)
				if (Choosen_Runway->Lflight->size > iRunways->data->Lflight->size)
					Choosen_Runway = iRunways;
		iRunways = iRunways->pNext;
	}
		
	if (Choosen_Runway->runway_num != 999999)
		return addFlight(Choosen_Runway, new_flight);
	else
		return FAILURE;
}

departFromRunway