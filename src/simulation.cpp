/* Main
 ***************************************************************
 * The main code that will run the simulation
 */

// #include <iostream>
// #include "handover_management.h"
#include "event_handler.h"
// #include "event_definitions.h"
#include "scheduler.h"
// #include "globals.h"
#include "bstations.h"
#include "hm.h"
#include "mobiles.h"
#include "prop.h"

/* Method
 ****************************
 * Return Type: int
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Main method that controls the simulation. It starts of by
 * setting up the basestations and mobiles, outputting, checking the
 * basestations and then outputting again.
 */

scheduler* gs = new scheduler();

double current_prop[] = {0.0,
				 		 0.0,
				 		 0.0,
				 		 0.0,
				 		 0.0,
				 		 0.0,
				 		 0.0,
				 		 0.0,
				 		 0.0};

double previous_prop[] = {0.0,
				 		  0.0,
				 		  0.0,
				 		  0.0,
				 		  0.0,
				 		  0.0,
				 		  0.0,
				 		  0.0,
				 		  0.0};

double TTT = 0.1;
double hys = 2.5;

bool handingOver = false;

int TTTtest[] = {TTT,
				 TTT,
				 TTT,
				 TTT,
				 TTT,
				 TTT,
				 TTT,
				 TTT,
				 TTT};

basestation* bStations[] = {new basestation(gs,0,0,0,1500,60,false),
							new basestation(gs,1,750,0,1500,60,false),
							new basestation(gs,2,1500,0,1500,60,false),
							new basestation(gs,3,0,750,1500,60,false),
							new basestation(gs,4,750,750,1500,60,true),
							new basestation(gs,5,1500,750,1500,60,false),
							new basestation(gs,6,0,1500,1500,60,false),
							new basestation(gs,7,750,1500,1500,60,false),
							new basestation(gs,8,1500,1500,1500,60,false)};

mobile* mobiles[] = {new mobile(gs,1,750,750,4,1)};

handover_management* hm = new handover_management(gs);

int main() {
	printf("Simulation started...\n");
	
	gs->start();

	printf("end...\n");

	delete gs;
	delete hm;

	return 0;
}
