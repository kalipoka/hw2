#include "airport.h"

/*Globals*/
static PAIRPORT PAirport;


///helper functions
PFLIGHT findFlightNum(int flightNum)
{
	PRUNWAY_ELEM iRunways = PAirport->head->pNext;
	if (!iRunways)
		return NULL;

	PFLIGHT_ELEM iFlights = iRunways->data->Lflight->head->pNext;

	while (!iRunways) {
		if (isFlightExists(iRunways->data, flightNum) == TRUE)
			return iRun;
		iRunways = iRunways->pNext;
	}
	return NULL;
}

BOOL findFlightDst(PRUNWAY i)
{
	PRUNWAY_ELEM iRunways = PAirport->head;
	PRUNWAY_ELEM iFlights = PAirport->head;

	while (tmp != NULL)
		while tmp
			if (tmp->data == i)
				return TRUE;
			else
				tmp = tmp->pNext;
	/* if we got here, it means that the element was not found */
	return FALSE;
}

PFLIGHT_SET createSet()
{
	PFLIGHT_SET s;
	s = (PFLIGHT_SET)malloc(sizeof(FLIGHT_SET));
	if (!s)
		return NULL;
	s->head = NULL;
	s->size = -1;
	return s;
}


BOOL findRunway(int rwN) /* rwN = runway Number*/
{
	PRUNWAY_ELEM tmp;
	int num;
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

departFromRunway