#include "handover_management.h"

/* Constructor
 ****************************
 * Return Type: N/A 
 ****************************
 * Parameters Passed in: N/A
 **************************** 
 * Description: Basic class constructor that create an instance of handover_management
 */
handover_management::handover_management(scheduler* gs) : event_handler(gs) {
	bStations[0] = new basestation(gs,1,0,0,2000,80);
	bStations[1] = new basestation(gs,2,50,0,2000,50);
	bStations[2] = new basestation(gs,3,100,0,2000,70);
	bStations[3] = new basestation(gs,4,0,50,2000,75);
	bStations[4] = new basestation(gs,5,50,50,2000,55);
	bStations[5] = new basestation(gs,6,100,50,2000,65);
	bStations[6] = new basestation(gs,7,0,100,2000,60);
	bStations[7] = new basestation(gs,8,50,100,2000,85);
	bStations[8] = new basestation(gs,9,100,100,2000,75);
	mobiles[0] = new mobile(gs,1,0,50,1,3);

	for(int i=0; i<1000; i++) {
		send_delay(new event(MOVE,mobiles[0]),(i*100.0));
		send_delay(new event(PRINT),((100.0*i)+50.0));
	}
}

handover_management::~handover_management() {
	globalScheduler->remove_from(this);
	globalScheduler->remove_to(this);
}

void handover_management::handler(const event* received)
{
	switch(received->label) {
		case MOVE:
			//send_now(new event(MOVE));
		case PRINT:
			send_now(new event(PRINT,mobiles[0]));
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
	double bestProp = 50000.0;
	double dist = 0.0;
	double prop = 0.0;
	double h = mobiles[0]->getHeight();
	int connected = mobiles[0]->getConnectedTo();
	int bestID = mobiles[0]->getConnectedTo();
	for(int i=0; i<(sizeof(bStations)/sizeof(*bStations)); i++) {
		dist = sqrt((abs((bStations[i]->getX()-mobiles[0]->getX()))^2) + (abs((bStations[i]->getY()-mobiles[0]->getY()))^2));
		printf("%d: dist: %f\n",i,dist);
		prop = bStations[i]->getProp(dist,h);
		printf("prop: %f\n",prop);
		if(prop < bestProp) {
			bestProp = prop;
			bestID = bStations[i]->getID();
		}
	}
	printf("bestProp: %f\n",bestProp);
	printf("bestID: %d\n",bestID);
	if(connected != bestID) {
    	mobiles[0]->switchBasestation(bestID);
	}
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
