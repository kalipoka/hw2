#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "flight.h"#include "ex2.h"int size_of_flight;size_of_flight = sizeof(PFLIGHT);PFLIGHT createFlight(int flight_num, FlightType flight_type, char destination[DEST_SIZE], BOOL emergency){	PFLIGHT pFlight;	pFlight = (PFLIGHT*)malloc(size_of_flight); /* MEMORY ALLOCATION*/	if (NULL == pFlight)		return NULL;	pFlight->flight_num = flight_num;	pFlight->flight_type = flight_type;	strcpy(pFlight->destination, destination);	pFlight->emergency = emergency;	return pFlight;}/*void destroyFlight(PFLIGHT pFlight){}Result printFlight(PFLIGHT pFlight){}*//*main for debugging*//*int main() {

	PFLIGHT pF;
	pF = createFlight(205, DOMESTIC, 'JFK', TRUE);
	printf("Number is %d", pF->flight_num);
	return 0;

}
*/
