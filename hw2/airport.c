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

Result addRunway(int Runway_num, FlightType Runway_type)
{
	if ((Runway_num < 0) && (Runway_num > MAX_ID))
		return FAILURE;
	
	PRUNWAY_ELEM tmp=
	
	if (findInSet(s, PFlight) == TRUE)
		/* element already exist in the set*/
		return TRUE;

	PRUNWAY_ELEM tmp;
	tmp = (PFLIGHT_ELEM)malloc(sizeof(FLIGHT_ELEM));
	if (!tmp) return FALSE;

	tmp->element = i;
	tmp->next = s->head;
	/* update the head */
	s->head = tmp;

	return TRUE;
}