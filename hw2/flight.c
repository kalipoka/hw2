/*hello alex*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "flight.h"#include "ex2.h"static PFLIGHT Fligh_Elements[MAX_ID] = { 0 };  /* array of flights structs*/static int counter = 0;int size_of_flight;size_of_flight = sizeof(PFLIGHT);PFLIGHT createFlight(int flight_num, FlightType flight_type, char destination[DEST_SIZE], BOOL emergency){	PFLIGHT pFlight;	if (counter > MAX_ID)  /* probably more checks of tkinut ha kelet are needed*/		return NULL;      /* are these cheks needed here or at other place at the codes*/	else	pFlight->flight_num = flight_num;	pFlight->flight_type = flight_type;	pFlight->destination = destination; /*wtf is this error?*/	pFlight->emergency = emergency;	return pFlight;}