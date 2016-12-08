#pragma once
#ifndef _AIRPORT_H_
#define _AIRPORT_H_

#include <stdio.h>
#include <stdlib.h>
#include "ex2.h"
#include "flight.h"
#include "runway.h"


typedef struct _RUNWAY_LIST_ELEM {
	PRUNWAY data;
	struct _RUNWAY_LIST_ELEM* pNext;
} RUNWAY_ELEM, *PRUNWAY_ELEM;


typedef struct _AIRPORT {
	PRUNWAY_ELEM head; /* head of the linked list */
} AIRPORT, *PAIRPORT;


Result addRunway(int, FlightType); //get number of a runway and type enter it to the end of the runway list...
Result removeRunway; // get the NUM of a runway and remove it from the airport
Result addFlightToAirport(); //add it lowest flight number and D/I and check if flight number already exists in the airport!
Result departFromRunway(int); //gets number of a Runway and departs the flight from it.
Result stormAlert(); // check all runways for destination with storm - remove and add it back at the end of the list. // check if dest is legal. //
void printAirport();

void destroyAirport();


#endif /*_AIRPORT_H_*/