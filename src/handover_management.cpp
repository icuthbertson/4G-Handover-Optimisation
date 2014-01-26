#include "handover_management.h"
#include <stdio.h>
#include <math.h>
// #include "mobile.h"
// #include "basestation.h"
#include "event_definitions.h"
// #include "globals.h"
#include "bstations.h"
#include "mobiles.h"
#include "prop.h"

// basestation* bStations[9];
// mobile* mobiles[1];	

/* Constructor
 ****************************
 * Return Type: N/A 
 ****************************
 * Parameters Passed in: N/A
 **************************** 
 * Description: Basic class constructor that create an instance of handover_management
 */
handover_management::handover_management(scheduler* gs) : event_handler(gs) {
	send_delay(new event(MOVE,mobiles[0]),0.0);
}
/* Method
 ****************************
 * Return Type: N/A 
 ****************************
 * Parameters Passed in:
 * const event* received
 ****************************
 * Description: Class hanlder that takes in a event and does the
 * required action depending on the event that was received.
 */
handover_management::~handover_management() {
	globalScheduler->remove_from(this);
	globalScheduler->remove_to(this);
}
/* Destructor
 ****************************
 * Return Type: N/A 
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Class destrcutor that removes an instance of this class
 * from the schedular and any messages still waiting to be passed.
 */
void handover_management::handler(const event* received)
{
	switch(received->label) {
		case PROP:
			break;
   		case POLL:
   			break;
		case PRINT:
			break;
		default:
			// program should not reach here
			break;
	} // end switch statement
}

/* Method
 ****************************
 * Return Type: int
 ****************************
 * Parameters Passed in: int connected
 ****************************
 * Description: Method that analysis the values it has and based on those values makes
 * 				a decision on what basestation the mobile should be connected to and
 *				if the basestation is different then the mobile is connected to the new
 *				"best" basestation.
 */
void handover_management::makeDecision() {
	// double bestProp = 50000.0;
	// double dist = 0.0;
	// double prop = 0.0;
	// double h = mobiles[0]->getHeight();
	// int connected = mobiles[0]->getConnectedTo();
	// int bestID = mobiles[0]->getConnectedTo();
	// for(int i=0; i<(sizeof(bStations)/sizeof(*bStations)); i++) {
	// 	dist = sqrt((abs((bStations[i]->getX()-mobiles[0]->getX()))^2) + (abs((bStations[i]->getY()-mobiles[0]->getY()))^2));
	// 	printf("%d: dist: %f\n",i,dist);
	// 	prop = bStations[i]->getProp(dist,h);
	// 	printf("prop: %f\n",prop);
	// 	if(prop < bestProp) {
	// 		bestProp = prop;
	// 		bestID = bStations[i]->getID();
	// 	}
	// }
	// printf("bestProp: %f\n",bestProp);
	// printf("bestID: %d\n",bestID);
	// if(connected != bestID) {
 //    	mobiles[0]->switchBasestation(bestID);
	// }
}
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that prints out all the information about
 * the mobiles and basestaions being used in the simulation.
 */
void handover_management::output() {
	mobiles[0]->print();
	for(int i=0; i<9; i++) {
		bStations[i]->print();
	}
}
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in: int index
 ****************************
 * Description: Method that calls the move method for a specified mobile.
 */
void handover_management::moveMobile(int index) {
	send_now(new event(MOVE, mobiles[0]));
}

// basestation* getBasestation(int id) {
// 	return bStations[id];
// }

// mobile* getMobile(int id) {
// 	return mobiles[id];
// }
