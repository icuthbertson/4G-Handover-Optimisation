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
#include <random>
#include <fstream>
#include <string>
#include <sstream>

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

double TTTArray[16];
double hysArray[21];

int TTTindex[] = {7,
			  	  7,
			  	  7,
			  	  7,
			  	  7,
			  	  7,
			  	  7,
			  	  7,
			  	  7};
int hysindex[] = {10,
			  	  10,
			  	  10,
			  	  10,
			  	  10,
			  	  10,
			  	  10,
			  	  10,
			  	  10};

int TTTmaxindex;
int hysmaxindex;

double TTTtest[NUM_BASESTATION];

double TTT[NUM_BASESTATION];
double hys[NUM_BASESTATION];

bool handingOver[] = {false,
					  false,
					  false,
					  false,
					  false,
					  false,
					  false,
					  false,
					  false};

int drop[] = {0,
			  0,
			  0,
			  0,
			  0,
			  0,
			  0,
			  0,
			  0};
int pingpongCount[] = {0,
			  		   0,
			  		   0,
			  		   0,
			  		   0,
			  		   0,
			  		   0,
			  		   0,
			  		   0};
int handovers[] = {0,
			  	   0,
			  	   0,
			  	   0,
			  	   0,
			  	   0,
			  	   0,
			  	   0,
			  	   0};

int rewardDrop[] = {0,
			  	    0,
			  	    0,
			  	    0,
			  	    0,
			  	    0,
			  	    0,
			  	    0,
			  	    0};
int rewardPing[] = {0,
			  	    0,
			  	    0,
			  	    0,
			  	    0,
			  	    0,
			  	    0,
			  	    0,
			  	    0};
int rewardHandover[] = {0,
			  	        0,
			  	        0,
			  	        0,
			  	        0,
			  	        0,
			  	        0,
			  	        0,
			  	        0};

int previous_id = 0;

double simTime[] = {0.0,
					0.0,
					0.0,
					0.0,
					0.0,
					0.0,
					0.0,
					0.0,
					0.0,
					0.0};

int function;

// basestation* bStations[] = {new basestation(gs,0,500,500,2000,60,false),
// 							new basestation(gs,1,3750,0,2000,60,false),
// 							new basestation(gs,2,6250,2000,2000,60,false),
// 							new basestation(gs,3,0,4000,2000,60,false),
// 							new basestation(gs,4,3000,3000,2000,60,true),
// 							new basestation(gs,5,6000,5000,2000,60,false),
// 							new basestation(gs,6,3000,6000,2000,60,false),
// 							new basestation(gs,7,0,7500,2000,60,false),
// 							new basestation(gs,8,3000,9000,2000,60,false),
// 							new basestation(gs,9,6000,8000,2000,60,false)};

basestation* bStations[] = {new basestation(gs,0,500,500,2000,60),
							new basestation(gs,1,2000,0,2000,60),
							new basestation(gs,2,3500,500,2000,60),
							new basestation(gs,3,0,2000,2000,60),
							new basestation(gs,4,2000,2000,2000,60),
							new basestation(gs,5,4000,2000,2000,60),
							new basestation(gs,6,500,3500,2000,60),
							new basestation(gs,7,2000,4000,2000,60),
							new basestation(gs,8,3500,3500,2000,60)};

mobile* mobiles[] = {new mobile(gs,0,500,500,0,1),
				 	 new mobile(gs,1,2000,0,1,1),
				 	 new mobile(gs,2,3500,500,2,1),
				 	 new mobile(gs,3,0,2000,3,1),
				 	 new mobile(gs,4,2000,2000,4,1),
				 	 new mobile(gs,5,4000,2000,5,1),
				 	 new mobile(gs,6,500,3500,6,1),
				 	 new mobile(gs,7,2000,4000,7,1),
				 	 new mobile(gs,8,3500,3500,8,1),
				 	 new mobile(gs,9,500,500,0,1)};


q_learning* q[NUM_BASESTATION];

std::vector<double> handover_total[] = {std::vector<double>(),
    								 	std::vector<double>(),
    								 	std::vector<double>(),
    								 	std::vector<double>(),
    								 	std::vector<double>(),
    								 	std::vector<double>(),
    								 	std::vector<double>(),
    								 	std::vector<double>(),
    								 	std::vector<double>()};

std::vector<double> drop_total[] = {std::vector<double>(),
    								std::vector<double>(),
    								std::vector<double>(),
    								std::vector<double>(),
    								std::vector<double>(),
    								std::vector<double>(),
    								std::vector<double>(),
    								std::vector<double>(),
    								std::vector<double>()};

std::vector<double> pingpong_total[] = {std::vector<double>(),
    								 	std::vector<double>(),
    								 	std::vector<double>(),
    								 	std::vector<double>(),
    								 	std::vector<double>(),
    								 	std::vector<double>(),
    								 	std::vector<double>(),
    								 	std::vector<double>(),
    								 	std::vector<double>()};

std::vector<int> stateChanges[] = {std::vector<int>(),
    							   std::vector<int>(),
    							   std::vector<int>(),
    							   std::vector<int>(),
    							   std::vector<int>(),
    							   std::vector<int>(),
    							   std::vector<int>(),
    							   std::vector<int>(),
    							   std::vector<int>()};

std::string handoverString;
std::string dropString;
std::string pingString;
std::string stateString;

int main(int run_num, int seed) {
	// srand(time(0));
    srand(seed);

	TTTmaxindex = 15;
	hysmaxindex = 20;

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

	// TTTindex = rand()%(TTTmaxindex+1);
	// hysindex = rand()%(hysmaxindex+1);



	for(int i=0; i<NUM_BASESTATION; i++) {
		TTT[i] = TTTArray[TTTindex[i]];
		hys[i] = hysArray[hysindex[i]];
	}

	std::cout << "Enter what operation you would like to undertake.\n";
	std::cout << "1 for generating / updating policy\n";
	std::cout << "2 for using the policy\n";
	std::cout << "3 for no learning\n";
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
	}  else if(arg == 3) {
		printf("No learning simulation...\n");
		printf("Enter index for TTT\n");
		int tempTTTindex;
		std::cin >> tempTTTindex;
		for(int j=0; j<NUM_BASESTATION; j++) {
			TTT[j] = TTTArray[tempTTTindex];
			TTTindex[j] = tempTTTindex;
		}
		printf("Enter index for hys\n");
		int temphysindex;
		std::cin >> temphysindex;
		for(int k=0; k<NUM_BASESTATION; k++) {
			hys[k] = hysArray[temphysindex];
			hysindex[k] = temphysindex;
		}
		function = 4;
	}

	q[0] = new q_learning(gs,0,TTTindex[0],hysindex[0]);
	q[1] = new q_learning(gs,1,TTTindex[1],hysindex[1]);
	q[2] = new q_learning(gs,2,TTTindex[2],hysindex[2]);
	q[3] = new q_learning(gs,3,TTTindex[3],hysindex[3]);
	q[4] = new q_learning(gs,4,TTTindex[4],hysindex[4]);
	q[5] = new q_learning(gs,5,TTTindex[5],hysindex[5]);
	q[6] = new q_learning(gs,6,TTTindex[6],hysindex[6]);
	q[7] = new q_learning(gs,7,TTTindex[7],hysindex[7]);
	q[8] = new q_learning(gs,8,TTTindex[8],hysindex[8]);

	gs->start();

	for (int l=0; l<NUM_BASESTATION; l++)
	{
		bStations[l]->print();
		q[l]->print();
	}

	for(int m=0; m<NUM_BASESTATION; m++) {
		std::stringstream hString;
		hString << "results/fading/optmid" << run_num << "/basestation" << m << "/handover.txt";
		handoverString = hString.str();

		std::stringstream dString;
		dString<< "results/fading/optmid" << run_num << "/basestation" << m << "/drop.txt";
		dropString = dString.str();

		std::stringstream pString;
		pString << "results/fading/optmid" << run_num << "/basestation" << m << "/ping.txt";
		pingString = pString.str();

		std::stringstream sString;
		sString << "results/fading/optmid" << run_num << "/basestation" << m << "/state.txt";
		stateString = sString.str();



		std::ofstream hFile (handoverString);
		if(hFile.is_open()) {
			for (std::vector<double>::iterator it=handover_total[m].begin() ; it!=handover_total[m].end(); it++) {
    		    hFile << *it << "\n";
    		}
    	}
    	hFile.close();

    	std::ofstream dFile (dropString);
		if(dFile.is_open()) {
			for (std::vector<double>::iterator it=drop_total[m].begin() ; it!=drop_total[m].end(); it++) {
    		    dFile << *it << "\n";
    		}
    	}
    	dFile.close();

    	std::ofstream pFile (pingString);
		if(pFile.is_open()) {
			for (std::vector<double>::iterator it=pingpong_total[m].begin() ; it!=pingpong_total[m].end(); it++) {
    		    pFile << *it << "\n";
    		}
    	}
    	pFile.close();

    	std::ofstream sFile (stateString);
		if(sFile.is_open()) {
			for (std::vector<int>::iterator it=stateChanges[m].begin() ; it!=stateChanges[m].end(); it++) {
    		    sFile << *it << "\n";
    		}
    	}
    	sFile.close();
    }

	printf("end...\n");

	delete gs;

	return 0;
}
