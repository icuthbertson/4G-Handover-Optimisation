/* Main
 ***************************************************************
 * The main code that will run the simulation
 */

#include <iostream>
#include "handover_management.h"
#include "event_handler.h"
#include "event_definitions.h"
#include "scheduler.h"
#include "event_definitions.h"

scheduler gs;
handover_management hm(&gs);
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
	
	for(int i=0; i<1000; i++) {
		hm.moveMobile(1);
		hm.makeDecision();
	}
	
	printf("end...\n");
	return 0;
}
