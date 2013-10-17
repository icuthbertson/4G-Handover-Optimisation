#include <iostream>
#include "basestation.hpp"
#include "mobile.hpp"

basestation bStations[9];
mobile mob1;

int setup() {
	bStations[0] = basestation(1,0,0,50);
	bStations[1] = basestation(2,50,0,50);
	bStations[2] = basestation(3,100,0,50);
	bStations[3] = basestation(4,0,50,50);
	bStations[4] = basestation(5,50,50,50);
	bStations[5] = basestation(6,100,50,50);
	bStations[6] = basestation(7,0,100,50);
	bStations[7] = basestation(8,50,100,50);
	bStations[8] = basestation(9,100,100,50);
	mob1.setmobile(1,0,0,50.0);
	return 0;
}

int output() {
	mob1.print();
	for(int i=0; i<9; i++) {
		bStations[i].print();
	}
	return 0;
}

int main() {
	printf("Simulation started...\n");

	setup();
	output();

	printf("end...\n");
	return 0;
}
