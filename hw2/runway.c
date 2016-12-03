#include "runway.h"
#include "ex2.h"



void* create_runway(int RunwayNum, FlightType type) // return an id to the created runway
{
	if ((type != DOMESTIC) && (type != INTERNATIONAL) || ((RunwayNum < 0) && RunwayNum > MAX_ID))
		return NULL;

	PRUNWAY PRunway;
	PRunway = (PRUNWAY) malloc(sizeof(RUNWAY));
	if (PRunway == NULL)
		return NULL;

	PRunway->type=type;
	PRunway->runway_num = RunwayNum;
	PRunway->PFflight = NULL;

	return PRunway;
}

void destroyRunway(PRUNWAY PRunway)  /* destroy the runway and waiting list in the runway - using runway pointer*/
{
	PRUNWAY pElem = NULL; // is declared for this function so we can use a temp flight list.
	while (PRunway->PFflight) { //free each flight independly
		pElem->PFflight = PRunway->PFflight;
		PRunway->PFflight = PRunway->PFflight->pNext;
		free(pElem->PFflight); //free each flight independly
	}
	free(PRunway);
}

BOOL isFlightExists(PRUNWAY PRunway, int flight_num)
/*Return True if flight exists else return False - using flight pointer*/
{
	if (!(PRunway != NULL))
		if (!((flight_num >= 0) && (flight_num <= MAX_ID)))
			return FALSE; // error in input flight-num not in range or Runway pointer is NULL
	
	PFLIGHT_LIST_ELEM pElem = PRunway->PFflight;

	while (pElem)
	{
		
		if (pElem->data->flight_num == flight_num)
			return TRUE;
		pElem = pElem->pNext;
	}
	return FALSE; //Not found in flight list
}

int getFlightNum(PRUNWAY PRunway) /*number of flights waiting - using runway pointer*/
{
	if (PRunway == NULL)
		return -1;
	PFLIGHT_LIST_ELEM pElem = PRunway->PFflight;
	int count = 0;
	while (pElem != NULL)
	{
		count++;
		pElem = pElem->pNext;
	}
	return count;
}


Result addFlight(PRUNWAY PRunway, PFLIGHT Pflight) /*Inserts a flight to the runway - using runway and flight pointer*/
{ 
		//fail for invalid parameter or malloc
	if ((PRunway == NULL) || (Pflight == NULL))
		return FAILURE;

	PFLIGHT_LIST_ELEM pElem = PRunway->PFflight;
	
	return SUCCESS;
}


Result removeFlight(void*, void*); /*remove a flight from a runway -  using runway and flight pointer*/

Result depart(void*); /*Removes the first flight in line - using runway_pointer*/

Result printRunway(void*); /*Prints the runway details, and flight list assigned to it - using runway_pointer*/


int main()
{
	PRUNWAY pointer;

	/*
	pointer = create_runway(1, INTERNATIONAL);
	if (pointer != NULL)
	{
		printf("%c\n", pointer->type);
		printf("%c", pointer->runway_num);
	}else
		printf("shit");
	int* something;
	*/
	return 0;

}
