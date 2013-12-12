/* Main
 ***************************************************************
 * The main code that will run the simulation
 */

#include <iostream>
#include <math.h>
#include "basestation.h"
#include "mobile.h"

basestation bStations[9];
mobile mobiles[9];
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that populates the array of basestations
 * and mobiles.
 */
void setup() {
	bStations[0] = basestation(1,0,0,1500,69);
	bStations[1] = basestation(2,50,0,1500,69);
	bStations[2] = basestation(3,100,0,1500,69);
	bStations[3] = basestation(4,0,50,1500,69);
	bStations[4] = basestation(5,50,50,1500,69);
	bStations[5] = basestation(6,100,50,1500,69);
	bStations[6] = basestation(7,0,100,1500,69);
	bStations[7] = basestation(8,50,100,1500,69);
	bStations[8] = basestation(9,100,100,1500,69);
	mobiles[0] = mobile(1,0,50,1,2);
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
void output() {
	mobiles[0].print();
	for(int i=0; i<9; i++) {
		bStations[i].print();
	}
}
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that decides the which basestation the current
 * mobile should be connected to by finding the best transmission strength
 * from all the basestations.
 * ***This method will be updated greatly when I have more knowledge***
 * ***just a basic method right now***
 */
void checkBasestations() {
	double bestProp = 123456789;
	double dist = 0.0;
	double prop = 0.0;
	double h = mobiles[0].getHeight();
	int connected = mobiles[0].getConnectedTo();
	int bestID = mobiles[0].getConnectedTo();
	for(int i=0; i<(sizeof(bStations)/sizeof(*bStations)); i++) {
		dist = sqrt((abs((bStations[i].getX()-mobiles[0].getX()))^2) + (abs((bStations[i].getY()-mobiles[0].getY()))^2));
		printf("%d: dist: %f\n",i,dist);
		//prop = bStations[i].getProp(dist,h);
		//printf("prop: %f\n",prop);
		//if(prop > bestProp) {
		//	bestProp = prop;
		//	bestID = bStations[i].getID();
		//}
		if(dist < bestProp) {
			bestProp = dist;
			bestID = bStations[i].getID();
		}
	}
	//printf("bestProp: %f\n",bestProp);
	printf("bestID: %d\n",bestID);
	if(connected != bestID) {
    	mobiles[0].switchBasestation(bestID);
	}
}
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

	setup();
	
	for(int i=0; i<1000; i++) {
		mobiles[0].moveRandom();
		checkBasestations();
		printf("%d: Connected: %d\n",i,mobiles[0].getConnectedTo());
		mobiles[0].printCos();
	}
	
	printf("end...\n");
	return 0;
}
