#include "runway.h"
#include "ex2.h"


void* create_runway(int RunwayNum, FlightType type) // return an pointer to the created runway
{
	if ((type != DOMESTIC) && (type != INTERNATIONAL) || ((RunwayNum < 0) && RunwayNum > MAX_ID))
		return NULL;

	PRUNWAY PRunway;
	PRunway = (PRUNWAY) malloc(sizeof(RUNWAY));
	if (PRunway == NULL)
		return NULL;

	PRunway->type=type;
	PRunway->runway_num = RunwayNum;

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
	if (PRunway == NULL)
		return FALSE;
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

Result addFlight(PRUNWAY PRunway, PFLIGHT Pflight) /*Inserts a flight to the runway - using runway and flight pointer- WATING FOR ALEX so could be done*/
{ 
		//fail for invalid parameter or malloc
	if ((PRunway == NULL) || (Pflight == NULL))
		return FAILURE;

	//check if flight type matches runway 
	if (Pflight->flight_type != PRunway->type)
		return FAILURE;

	//create a copy of the flight
	PFLIGHT new_Pflight  = createFlight(Pflight->flight_num, Pflight->flight_type, Pflight->destination, Pflight->emergency);

	PFLIGHT_LIST_ELEM Plast_flight = PRunway->PFflight;
	printf("nice one");
	while (Plast_flight->pNext != NULL)
	{
		printf("ohh yeah" );
		Plast_flight = Plast_flight->pNext;
	}
	printf("nice two");
	Plast_flight->pNext = new_Pflight;
	
	
	return SUCCESS;
}
	
Result removeFlight(PRUNWAY PRunway, int flight_num) /*remove a flight from a runway -  using runway and flight pointer*/
{
	if (PRunway == NULL)
		return FAILURE;
	if (!((flight_num >= 0) && (flight_num <= MAX_ID)))
		return FAILURE; // error in input flight-num not in range or Runway pointer is NULL

	PFLIGHT_LIST_ELEM pElem = PRunway->PFflight;
	PFLIGHT_LIST_ELEM pPrev = NULL;
	while (pElem)
	{
		if (pElem->data->flight_num == flight_num)
		{
			pPrev->pNext = pElem->pNext;
			destroyFlight(pElem);
			return SUCCESS;
		}
		pPrev = pElem;
		pElem = pElem->pNext;
	}
	return FAILURE; //Not found in flight list
}

Result depart(PRUNWAY PRunway) /*Removes the first flight in line - using runway_pointer*/
{
	if ((PRunway->PFflight == NULL) || (PRunway==NULL))
		return FAILURE;
	else
		return removeFlight(PRunway, PRunway->PFflight->data->flight_num);
}

Result printRunway(PRUNWAY PRunway) /*Prints the runway details, and flight list assigned to it - using runway_pointer*/
{
	if (PRunway == NULL)
		return FAILURE;
	printf("Runway %d ", PRunway->runway_num);
	if (PRunway->type == INTERNATIONAL)
		printf("international\n");
	else
		printf("domestic\n");

	PFLIGHT_LIST_ELEM tmp = PRunway->PFflight->pNext;
	while (tmp)
	{
		//printFlight(tmp);
		tmp = tmp->pNext;
	}
	return SUCCESS;
}


int main()
{
	PRUNWAY pointer;

	
	pointer = create_runway(1, DOMESTIC);
	/*
	if (pointer != NULL)
	{
		printf("%c\n", pointer->type);
		printf("%c", pointer->runway_num);
	}else
		printf("shit");
	int* something;
	*/

	PFLIGHT pFlight3 = createFlight(3, DOMESTIC, "HFA", TRUE);
	PFLIGHT pFlight4 = createFlight(4, DOMESTIC, "JRS", TRUE);

	if (addFlight(pointer, pFlight3) == FAILURE) printf("FAIL\n");
	if (addFlight(pointer, pFlight4) == FAILURE) printf("FAIL\n");

	printRunway(pointer);
	destroyRunway(pointer);
	
	return 0;

}
/*

*/
