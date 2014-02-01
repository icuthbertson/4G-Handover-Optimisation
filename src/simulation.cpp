/* Main
 ***************************************************************
 * The main code that will run the simulation
 */

// #include <iostream>
#include "event_handler.h"
#include "scheduler.h"
#include "bstations.h"
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

double TTT = 1.024;
double hys = 7.5;

bool handingOver = false;

int drop = 0;
int pingpongCount = 0;
int handovers = 0;

int previous_id = 0;

bool deadzone = false;
int deadzoneRecovers = 0;

double simTime = 0.0;

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

int main() {
	printf("Simulation started...\n");
	
	gs->start();

	printf("end...\n");

	delete gs;

	return 0;
}
