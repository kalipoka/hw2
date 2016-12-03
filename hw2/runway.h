#pragma once
#ifndef _RUNWAY_H_
#define _RUNWAY_H_

#include <stdio.h>
#include <stdlib.h>
#include "ex2.h"
#include "flight.h"


typedef struct _FLIGHT_LIST_ELEM {
	PFLIGHT data;
	struct _LIST_ELEMENT* pNext;
} FLIGHT_LIST_ELEM, *PFLIGHT_LIST_ELEM;


typedef struct _RUNWAY
{
	unsigned int runway_num;
	FlightType type;
	PFLIGHT_LIST_ELEM PFflight; //Contains the first flight on list pointer
} RUNWAY, *PRUNWAY;


void* create_runway(int, FlightType); /*return an id to the created runway*/
void destroyRunway(PRUNWAY);  /* destroy the runway and waiting list in the runway*/
BOOL isFlightExists(PRUNWAY, int); /*Return True if flight exists else return False - using flight pointer and runway*/
int getFlightNum(PRUNWAY); /*number of flights waiting - using runway pointer*/
Result addFlight(PRUNWAY, PFLIGHT); /*Inserts a flight to the runway - using runway and flight pointer*/
Result removeFlight(PRUNWAY, PFLIGHT); /*remove a flight from a runway -  using runway and flight pointer*/
Result depart(PRUNWAY); /*Removes the first flight in line - using runway_pointer*/
Result printRunway(PRUNWAY); /*Prints the runway details, and flight list assigned to it - using runway_pointer*/

#endif /*_RUNWAY_H_*/