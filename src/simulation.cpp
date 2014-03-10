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
#include "q.h"
#include <iostream>
#include "simple.h"
#include <random>

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

double current_prop[9];

double TTTArray[16];

double hysArray[21];

int TTTindex;
int hysindex;

int TTTmaxindex;
int hysmaxindex;

double TTT;
double hys;

bool handingOver = false;

int drop = 0;
int pingpongCount = 0;
int handovers = 0;

int rewardDrop = 0;
int rewardPing = 0;
int rewardHandover = 0;

int previous_id = 0;

bool deadzone = false;
int deadzoneRecovers = 0;

double simTime = 0.0;

int function;

double TTTtest[] = {TTT,
				 	TTT,
				 	TTT,
				 	TTT,
				 	TTT,
				 	TTT,
				 	TTT,
				 	TTT,
				 	TTT};

basestation* bStations[] = {new basestation(gs,0,0,0,1500,60,false),
							new basestation(gs,1,1000,0,1500,60,false),
							new basestation(gs,2,2000,0,1500,60,false),
							new basestation(gs,3,0,1000,1500,60,false),
							new basestation(gs,4,1000,1000,1500,60,true),
							new basestation(gs,5,2000,1000,1500,60,false),
							new basestation(gs,6,0,2000,1500,60,false),
							new basestation(gs,7,1000,2000,1500,60,false),
							new basestation(gs,8,2000,2000,1500,60,false)};

mobile* mobiles[] = {new mobile(gs,1,1000,1000,4,1)};

q_learning* q;
simple_learning* simple;

int main() {
	srand(time(0));

	TTTmaxindex = 15;
	hysmaxindex = 20;

	current_prop[0] = 0.0;
	current_prop[1] = 0.0;
	current_prop[2] = 0.0;
	current_prop[3] = 0.0;
	current_prop[4] = 0.0;
	current_prop[5] = 0.0;
	current_prop[6] = 0.0;
	current_prop[7] = 0.0;
	current_prop[8] = 0.0;

	TTTArray[0] = 0.0;
	TTTArray[1] = 0.04;
	TTTArray[2] = 0.064;
	TTTArray[3] = 0.08;
	TTTArray[4] = 0.1;
	TTTArray[5] = 0.128;
	TTTArray[6] = 0.16;
	TTTArray[7] = 0.256;
	TTTArray[8] = 0.32;
	TTTArray[9] = 0.48;
	TTTArray[10] = 0.512;
	TTTArray[11] = 0.64;
	TTTArray[12] = 1.024;
	TTTArray[13] = 1.280;
	TTTArray[14] = 2.56;
	TTTArray[15] = 5.12;

	hysArray[0] = 0.0;
	hysArray[1] = 0.5;
	hysArray[2] = 1.0;
	hysArray[3] = 1.5;
	hysArray[4] = 2.0;
	hysArray[5] = 2.5;
	hysArray[6] = 3.0;
	hysArray[7] = 3.5;
	hysArray[8] = 4.0;
	hysArray[9] = 4.5;
	hysArray[10] = 5.0;
	hysArray[11] = 5.5;
	hysArray[12] = 6.0;
	hysArray[13] = 6.5;
	hysArray[14] = 7.0;
	hysArray[15] = 7.5;
	hysArray[16] = 8.0;
	hysArray[17] = 8.5;
	hysArray[18] = 9.0;
	hysArray[19] = 9.5;
	hysArray[20] = 10.0;

	TTTindex = rand()%(TTTmaxindex+1);
	hysindex = rand()%(hysmaxindex+1);

	// TTTindex = 15;
	// hysindex = 20;

	TTT = TTTArray[TTTindex];
	hys = hysArray[hysindex];

	std::cout << "Enter what operation you would like to undertake.\n";
	std::cout << "1 for generating / updating policy\n";
	std::cout << "2 for using the policy\n";
	std::cout << "3 for simple learning\n";
	std:: cout << "Please enter:\n";

	int arg;
	std::cin >> arg;

	if(arg == 1) {
		// q-learning
		printf("Q-Learning started...\n");
		function = 1;
	} else if(arg == 2) {
		// use policy
		printf("Simulation started...\n");
		function = 2;
	} else if(arg == 3) {
		printf("Simple-Learning started...\n");
		function = 3;
	}

	q = new q_learning(gs,TTTindex,hysindex);

	simple = new simple_learning(gs);

	gs->start();

	if(function == 1) {
		q->print();
	}

	printf("end...\n");

	delete gs;

	return 0;
}
