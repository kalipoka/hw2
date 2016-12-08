#include "airport.h"

/*Globals*/
static PAIRPORT PAirport;
static PRUNWAY_ELEM Prun;


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

PRUNWAY findRunway(int rwN) /* rwN = runway Number*/
{
	PRUNWAY_ELEM tmp = PAirport->head;
	while (!tmp)
		if (tmp->data->runway_num == rwN)
			return tmp->data;
		else
			tmp = tmp->pNext;
	/* if we got here, it means that the runway was not found */
	return NULL;
}

//Functions

Result addRunway(int Runway_num, FlightType Runway_type)
{
	/* check is the number is legal*/
	if ((Runway_num < 0) || (Runway_num > MAX_ID))
		return FAILURE;
	
	PRUNWAY_ELEM tmp;
	tmp = (PRUNWAY_ELEM)malloc(sizeof(RUNWAY_ELEM));
	if (!tmp) return FALSE;
	tmp->data = create_runway(Runway_num, Runway_type);
	tmp->pNext = NULL;

	if (!PAirport->head)
	{
		PAirport->head = tmp;
		
		return SUCCESS;
	}

	if (findRunway(Runway_num)) /* element already exist in the set*/
		return FAILURE;

	/* update the head */
	PRUNWAY_ELEM last_runway = PAirport->head;
	while (last_runway->pNext != NULL)
		last_runway = last_runway->pNext;
	last_runway->pNext = tmp;

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
			return SUCCESS;
		}
		prevR = currentR;
		currentR = currentR->pNext;
	}
	return FAILURE;
}

Result addFlightToAirport(int flight_num, FlightType flight_type, char destination[DEST_SIZE], BOOL emergency)
{

	PRUNWAY_ELEM iRunways = PAirport->head;
	PRUNWAY Choosen_Runway = NULL;
	PFLIGHT new_flight = createFlight(flight_num, flight_type, destination, emergency);
	if (!new_flight)
		return FAILURE;
	
	while (iRunways)
	{
		if (iRunways->data->type == flight_type) /*is it the right flight type*/
			if (isFlightExists(iRunways->data, flight_num) == FALSE) /*is the flight num exists */
				if (!Choosen_Runway)
					Choosen_Runway = iRunways->data;
				else if (Choosen_Runway->Lflight->size > iRunways->data->Lflight->size) /* check if runway is the smallest*/
					Choosen_Runway = iRunways->data;
		iRunways = iRunways->pNext;
	}
		
	if (Choosen_Runway)
		return addFlight(Choosen_Runway, new_flight);
	else
		return FAILURE;
}

Result departFromRunway(int runway_num)
{
	PRUNWAY tmp = findRunway(runway_num);
	if (!tmp) return FAILURE;
	return depart(tmp);
}

Result stormAlert(char destination[DEST_SIZE])
{
	PRUNWAY_ELEM iRunways = PAirport->head;

	while (!iRunways) {
		PFLIGHT_ELEM iFlights = iRunways->data->Lflight->head->pNext;
		while (iFlights)
		{
			if (strcmp(iFlights->data->destination, destination)) {
				int n = iFlights->data->flight_num;
				FlightType flight_type= iFlights->data->flight_type;
				BOOL emergency = iFlights->data->emergency;
				if (removeFlight(iRunways->data, n) == FAILURE) return FAILURE;
				if (addFlightToAirport(n,flight_type,destination,emergency) == FAILURE) return FAILURE;
			}
			iFlights = iFlights->pNext;
		}
		iRunways = iRunways->pNext;
	}
	return SUCCESS;
}

void printAirport()
{
	PRUNWAY_ELEM iRunways = PAirport->head;
	printf("Airport status\n");
	while (iRunways) {
		printRunway(iRunways->data);
		iRunways = iRunways->pNext;
	}
	return;
}

void destroyAirport()
{
	PRUNWAY_ELEM iRunways = PAirport->head;
	PRUNWAY_ELEM tmp;
	printf("Airport status\n");
	while (!iRunways) {
		tmp = PAirport->head->pNext;
		destroyRunway(iRunways->data);
		iRunways = tmp;
	}
	free(PAirport);
	free(Prun);
}

int main()
{
	PAirport = (PAIRPORT)malloc(sizeof(AIRPORT));
	if (!PAirport) return NULL;

	PAirport->head = NULL;

	if (addRunway(1, DOMESTIC) == FAILURE) printf("FUCK THIS SHIT");
	if (addRunway(2, INTERNATIONAL) == FAILURE) printf("FUCK THIS SHIT");

	addFlightToAirport(3, DOMESTIC, "HFA", FALSE);
	addFlightToAirport(4, INTERNATIONAL, "JRS", FALSE);
	addFlightToAirport(5, DOMESTIC, "TLV", TRUE);
	addFlightToAirport(6, INTERNATIONAL, "BCN", FALSE);
	addFlightToAirport(7, DOMESTIC, "MAD", TRUE);

	removeRunway(2);
	printAirport();

	return 0;




}