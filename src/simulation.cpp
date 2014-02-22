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
// #include "q_learning.h"
#include "q.h"
#include <iostream>
// #include "opt.h"
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

double current_prop[] = {0.0,
				 		 0.0,
				 		 0.0,
				 		 0.0,
				 		 0.0,
				 		 0.0,
				 		 0.0,
				 		 0.0,
				 		 0.0};

double TTTArray[] = {0.0,
					 0.04,
					 0.064,
					 0.08,
					 0.1,
					 0.128,
					 0.16,
					 0.256,
					 0.32,
					 0.48,
					 0.512,
					 0.64,
					 1.024,
					 1.280,
					 2.56,
					 5.12};

double hysArray[] = {0.0,
					 0.5,
					 1.0,
					 1.5,
					 2.0,
					 2.5,
					 3.0,
					 3.5,
					 4.0,
					 4.5,
					 5.0,
					 5.5,
					 6.0,
					 6.5,
					 7.0,
					 7.5,
					 8.0,
					 8.5,
					 9.0,
					 9.5,
					 10.0};

int hys_weighting[] = {0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0};

int TTT_weighting[] = {0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0,
					   0};

int TTTindex;
int hysindex;

int TTTmaxindex = 16;
int hysmaxindex = 21;

double TTT;
double hys;

bool handingOver = false;

int drop = 0;
int pingpongCount = 0;
int handovers = 0;
int handoverFailures = 0;

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
							new basestation(gs,1,750,0,1500,60,false),
							new basestation(gs,2,1500,0,1500,60,false),
							new basestation(gs,3,0,750,1500,60,false),
							new basestation(gs,4,750,750,1500,60,true),
							new basestation(gs,5,1500,750,1500,60,false),
							new basestation(gs,6,0,1500,1500,60,false),
							new basestation(gs,7,750,1500,1500,60,false),
							new basestation(gs,8,1500,1500,1500,60,false)};

mobile* mobiles[] = {new mobile(gs,1,750,750,4,1)};

q_learning* q;

// optimise* learning  = new optimise(gs); 

void learn(int learn) {
	if(learn == 1) {
		if(TTTindex+1 <= TTTmaxindex) {
			TTTindex += 1;
			TTT = TTTArray[TTTindex];
		} 
		if(hysindex+1 <= hysmaxindex) {
			hysindex += 1;
			hys = hysArray[hysindex];
		}
	} else {
		if(TTTindex-1 >= 0) {
			TTTindex -= 1;
			TTT = TTTArray[TTTindex];
		} 
		if(hysindex-1 >= 0) {
			hysindex -= 1;
			hys = hysArray[hysindex];
		}
	}
}

int main() {
	srand(time(0));

	TTTindex = rand()%TTTmaxindex;
	hysindex = rand()%hysmaxindex;

	TTT = TTTArray[TTTindex];
	hys = hysArray[hysindex];

	std::cout << "Enter what operation you would like to undertake.\n";
	std::cout << "1 for generating / updating policy\n";
	std::cout << "2 for using the policy\n";
	std:: cout << "Please enter:\n";

	int arg;
	std::cin >> arg;

	if(arg == 1) {
		// q-learning
		printf("Q-Learning started...\n");
		function = 1;
	} else if (arg == 2) {
		// use policy
		printf("Simulation started...\n");
		function = 2;
	}

		q = new q_learning(gs,TTTindex,hysindex);

	gs->start();

	if(function == 1) {
		q->print();
	}

	printf("end...\n");

	delete gs;

	return 0;
}
