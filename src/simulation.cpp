/* Main
 ***************************************************************
 * The main code that will run the simulation
 */

#include <iostream>
#include <math.h>
#include "basestation.hpp"
#include "mobile.hpp"

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
	bStations[0] = basestation(1,0,0,0);
	bStations[1] = basestation(2,50,0,0);
	bStations[2] = basestation(3,100,0,0);
	bStations[3] = basestation(4,0,50,50);
	bStations[4] = basestation(5,50,50,0);
	bStations[5] = basestation(6,100,50,0);
	bStations[6] = basestation(7,0,100,0);
	bStations[7] = basestation(8,50,100,0);
	bStations[8] = basestation(9,100,100,0);
	mobiles[0] = mobile(1,0,0,50.0,1);
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
	double bestClosest = 10000000;
	int connected, bestID = mobiles[0].getConnectedTo();
	for(int i=0; i<(sizeof(bStations)/sizeof(*bStations)); i++) {
		if(sqrt((abs((bStations[i].getX()-mobiles[0].getX()))^2) + (abs((bStations[i].getY()-mobiles[0].getY()))^2)) < bestClosest) {
			bestClosest = sqrt((abs((bStations[i].getX()-mobiles[0].getX()))^2) + (abs((bStations[i].getY()-mobiles[0].getY()))^2));
			bestID = bStations[i].getID();
		}
	}
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
	output();

	checkBasestations();
	output();

	printf("end...\n");
	return 0;
}
