#pragma once
#ifndef _FLIGHT_H_
#define _FLIGHT_H_
#include "ex2.h"

/*The flight element*/
typedef struct _FLIGHT
{
	unsigned int flight_num;                     /*no to forget to limit with MAX_ID from ex2.h*/
	FlightType flight_type;            /*FlightType from from ex2.h*/
	char destination[DEST_SIZE];              /*is it the correct way to define string?*/
	BOOL emergency;                  /*is it emergency*/
} FLIGTH, *PFLIGHT;

/* Interface functions */

PFLIGHT createFlight(int, FlightType, char, BOOL);       /* Creates flight - returns pointer  - allocates memory*/
void destroyFlight(PFLIGHT);							/*needs to delete and free the memory*/
Result printFlight(PFLIGHT);                           /*prints flight details and Success or Failure of Null*/

#endif /* _FLIGHT_H_ */