#include "runway.h"


///helpers functions
BOOL findInSet(PFLIGHT_SET s, PFLIGHT i)
{
	PFLIGHT_ELEM tmp;
	if (!s)
		return FALSE;
	tmp = s->head;
	while (tmp != NULL)
		if (tmp->data->flight_num == i->flight_num) // we need to compare number of the flight
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

BOOL addToSet(PFLIGHT_SET s, PFLIGHT PFlight) {
	PFLIGHT_ELEM tmp;
	if (!s)
		return FALSE;
	if (findInSet(s, PFlight) == TRUE)
		/* element already exist in the set*/
		return FALSE;
	
	tmp = (PFLIGHT_ELEM)malloc(sizeof(FLIGHT_ELEM));
	if (!tmp) return FALSE;
	tmp->data = PFlight;
	tmp->pNext = NULL;
	
	if (s->head) {
		PFLIGHT_ELEM last_flight = s->head;
		while (last_flight->pNext != NULL)
			last_flight = last_flight->pNext;
		last_flight->pNext = tmp;
	}else 
		s->head = tmp;
	
	s->size++;
	return TRUE;
}


BOOL addToSet_Emergency(PFLIGHT_SET s, PFLIGHT PFlight) {
	PFLIGHT_ELEM tmp;
	if (!s) return FALSE;
	if (findInSet(s, PFlight) == TRUE) return FALSE;
		/* element already exist in the set*/

	tmp = (PFLIGHT_ELEM)malloc(sizeof(FLIGHT_ELEM));
	if (!tmp) return FALSE; /*malloc check*/
	
	tmp->data = PFlight;
	tmp->pNext = NULL;

	if (s->head) {
		PFLIGHT_ELEM last_flight = s->head;
		while ((last_flight->pNext) && (last_flight->pNext->data->emergency != FALSE))
			last_flight = last_flight->pNext;
		tmp->pNext = last_flight->pNext;
		last_flight->pNext = tmp;
	}
	else
		s->head = tmp;

	s->size++;
	return TRUE;
}

//////////////////

PRUNWAY create_runway(int RunwayNum, FlightType type) // return a pointer to the created runway
{
	if ((type != DOMESTIC) && (type != INTERNATIONAL) || ((RunwayNum < 0) && RunwayNum > MAX_ID))
		return NULL;

	PRUNWAY PRunway;
	PRunway = (PRUNWAY) malloc(sizeof(RUNWAY));
	if (!PRunway)
		return NULL;

	PRunway->Lflight = createSet();
	
	if (!PRunway->Lflight) return NULL;
	
	PFLIGHT pointer = createFlight(1, DOMESTIC, "AAA", TRUE);

	pointer->flight_num = 999999;
	
	addToSet(PRunway->Lflight, pointer);
	//PRunway->Lflight->head = pointer; // to set the head to be the fake;
	PRunway->type=type;
	PRunway->runway_num = RunwayNum;

	return PRunway;
}

void destroyRunway(PRUNWAY PRunway)  /* destroy the runway and waiting list in the runway - using runway pointer*/
{
	PFLIGHT_ELEM tmp = PRunway->Lflight->head;
	while (tmp)
	{
		PRunway->Lflight->head = tmp->pNext; //new head is the next elem
		destroyFlight(tmp->data); //destroy the current flight data
		free(tmp); //destroy the element
		tmp = PRunway->Lflight->head; //get the new head
	}
	free(PRunway->Lflight);
	free(PRunway);
}

BOOL isFlightExists(PRUNWAY PRunway, int flight_num)
/*Return True if flight exists else return False - using flight pointer*/
{
	if (!PRunway)
		return FALSE;
	if ((flight_num < 1) || (flight_num > MAX_ID))
		return FALSE;
	PFLIGHT_ELEM tmp = PRunway->Lflight->head->pNext;
	while (tmp)
	{
		if (tmp->data->flight_num == flight_num)
			return TRUE;
		tmp = tmp->pNext;
	}
	return FALSE; //Not found in flight list
}

int getFlightNum(PRUNWAY PRunway) /*number of flights waiting - using runway pointer*/
{
	if (!PRunway)
		return -1;
	return PRunway->Lflight->size;
}

Result addFlight(PRUNWAY PRunway, PFLIGHT Pflight) /*Inserts a flight to the runway - using runway and flight pointer- WATING FOR ALEX so could be done*/
{ 
	/*fail for invalid parameter or malloc*/
	if ((!PRunway) || (!Pflight))
		return FAILURE;

	/*check if flight type matches runway*/ 
	if (Pflight->flight_type != PRunway->type)
		return FAILURE;

	if (isFlightExists(PRunway, Pflight->flight_num) == TRUE) return FAILURE;
	
	/*create a copy of the flight*/
	PFLIGHT new_Pflight  = createFlight(Pflight->flight_num, Pflight->flight_type, Pflight->destination, Pflight->emergency);

	if (new_Pflight->emergency == TRUE) //
		if (addToSet_Emergency(PRunway->Lflight, new_Pflight) == TRUE)
			return SUCCESS;
		else
			return FAILURE;
	else //this isn't emergency flight
		if (addToSet(PRunway->Lflight, new_Pflight) == TRUE)
			return SUCCESS;
		else
			return FAILURE;
}
	
Result removeFlight(PRUNWAY PRunway, int flight_num) /*remove a flight from a runway -  using runway and flight num*/
{
	if (!PRunway)
		return FAILURE;
	if ((flight_num < 0) || (flight_num > MAX_ID))
		return FAILURE;

	PFLIGHT_ELEM  tmp = PRunway->Lflight->head->pNext;
	PFLIGHT_ELEM	pPrev = PRunway->Lflight->head;
	while (tmp)
	{
		if (tmp->data->flight_num == flight_num)
		{
			pPrev->pNext= tmp->pNext;
			destroyFlight(tmp->data);
			PRunway->Lflight->size--;
			return SUCCESS;
		}
		pPrev = tmp;
		tmp = tmp->pNext;
	}
	return FAILURE; //Not found in flight list
}

Result depart(PRUNWAY PRunway) /*Removes the first flight in line - using runway_pointer*/
{
	if (!PRunway) return FAILURE;
	if (!PRunway->Lflight->head->pNext) return FAILURE;
	return removeFlight(PRunway, PRunway->Lflight->head->pNext->data->flight_num);
}

Result printRunway(PRUNWAY PRunway) /*Prints the runway details, and flight list assigned to it - using runway_pointer*/
{
	if (!PRunway)
		return FAILURE;
	printf("Runway %d ", PRunway->runway_num);
	if (PRunway->type == INTERNATIONAL)
		printf("international\n");
	else
		printf("domestic\n");
	printf("%d flights are waiting:\n", PRunway->Lflight->size);
	PFLIGHT_ELEM tmp = PRunway->Lflight->head->pNext;
	while (tmp)
	{
		printFlight(tmp->data);
		tmp = tmp->pNext;
	}
	return SUCCESS;
}

/*
int main()
{

	PRUNWAY pointerI, pointerD;

	pointerI = create_runway(1, INTERNATIONAL);
	pointerD = create_runway(2, DOMESTIC);

	PFLIGHT pFlight3 = createFlight(3, DOMESTIC, "HFA", FALSE);
	PFLIGHT pFlight4 = createFlight(4, DOMESTIC, "JRS", FALSE);
	PFLIGHT pFlight5 = createFlight(5, DOMESTIC, "TLV", TRUE);
	PFLIGHT pFlight6 = createFlight(6, DOMESTIC, "BCN", FALSE);
	PFLIGHT pFlight7 = createFlight(7, DOMESTIC, "MAD", TRUE);

	PFLIGHT pFlight8 = createFlight(3, INTERNATIONAL, "HFA", FALSE);
	PFLIGHT pFlight9 = createFlight(4, INTERNATIONAL, "JRS", FALSE);

	
	if (addFlight(pointerD, pFlight3) == FAILURE) printf("FAIL1\n");
	if (addFlight(pointerD, pFlight4) == FAILURE) printf("FAIL2\n");
	if (addFlight(pointerD, pFlight4) == FAILURE) printf("FAIL3\n");
	if (addFlight(pointerD, pFlight5) == FAILURE) printf("FAIL4\n");
	if (addFlight(pointerD, pFlight6) == FAILURE) printf("FAIL5\n");
	if (addFlight(pointerD, pFlight7) == FAILURE) printf("FAIL6\n");
	if (addFlight(pointerI, pFlight8) == FAILURE) printf("FAIL7\n");
	if (addFlight(pointerI, pFlight9) == FAILURE) printf("FAIL8\n");

	printf("Number of flights in List: %d\n\n", getFlightNum(pointerD));
	if (isFlightExists(pointerI,3)==TRUE) printf("the flight exists!\n");
	if (isFlightExists(pointerD, 1) == FALSE) printf("the flight doesn't exists!\n");

	printRunway(pointerD);
	printRunway(pointerI);


	printf("\n");
	if (depart(pointerI) == FAILURE) printf("FAIL!!");
	printf("Number of flights in List I: %d\n\n", getFlightNum(pointerD));
	printf("Number of flights in List D: %d\n\n", getFlightNum(pointerI));
	printRunway(pointerI);
	destroyRunway(pointerI);
	destroyRunway(pointerD);

	
	return 0;

}
*/

