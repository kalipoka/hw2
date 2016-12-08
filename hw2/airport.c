#include "airport.h"

/*Globals*/
static PAIRPORT PAirport;

///helper functions 

BOOL findFlight(PRUNWAY i)
{
	PRUNWAY_ELEM tmp;
	tmp = s->head;
	while (tmp != NULL)
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
	tmp = (PRUNWAY_ELEM)malloc(sizeof(RUNWAY_ELEM));
	/* check memory allocation*/
	if (!tmp) return FALSE;


	/* create set*/
	PFLIGHT_SET s;
	s = (PFLIGHT_SET)malloc(sizeof(FLIGHT_SET));
	if (!s)
		return NULL;
	s->head = NULL;
	s->size = -1;
	return s;
	/* till here*/
	tmp->data = create_runway(Runway_num, Runway_type);
		runway_num = Runway_num;
	tmp->pNext = PAirport->head;

	/* update the head */
	PAirport->head = tmp;
	return SUCCESS;
}