/* Main
 ***************************************************************
 * The main code that will run the simulation
 */

// #include <iostream>
// #include "handover_management.h"
#include "event_handler.h"
// #include "event_definitions.h"
#include "scheduler.h"
#include "globals.h"

// scheduler gs;
// handover_management hm;
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
int main() {
	printf("Simulation started...\n");
	
	scheduler* gs = new scheduler();
	handover_management* hm = new handover_management(gs);
	gs->start();

	printf("end...\n");

	delete gs;
	delete hm;

	return 0;
}
