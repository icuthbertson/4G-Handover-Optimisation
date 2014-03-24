#include "actions.h"
#include "prop.h"
#include "event_definitions.h"
#include <random>
#include <fstream>
#include <iostream>
#include <sstream>

q_learning::q_learning(scheduler* gs, int id, int TTT, int hys) : event_handler(gs) {
	this->id = id;
	int startState = (TTT*21)+hys;
	printf("Start State: %d\n",startState);

	std::stringstream sstmq;
	sstmq << "q_arrays/q" << id << ".txt";
	qString = sstmq.str();

	std::stringstream sstmp;
	sstmp << "policy/policy" << id << ".txt";
	policyString = sstmp.str();

	double q = 0.0;
	std::ifstream qFile (qString);

	if(qFile.is_open()) {
		for(int i=0; i<NUMSTATES; i++) {
			for(int j=0; j<NUMSTATES; j++) {
				qFile>>q;
				Q[i][j] = q; //read Q in
			}
		}
	}

   	qFile.close();

	current_state = startState;
	action = 0;
	next_state = 0;
	firstPass = true;
	allActions = false;

	if(function == 1) {
		send_delay(new event(LEARN),180);
	} else if(function == 2) { //for using policy
		std::ifstream pFile (policyString);

		if(pFile.is_open()) {
			for(int i=0; i<NUMSTATES; i++) {
				pFile >> policyArray[i];
			}
		}
	}
}

q_learning::~q_learning() {
	globalScheduler->remove_from(this);
	globalScheduler->remove_to(this);
}

void q_learning::handler(const event* received)
{
	if(allActions == true) {
		globalScheduler->stop();
	}
	switch(received->label) {
		case LEARN:
			learn();
			break;
		case POLICY:
			//change state depending on policy
			changeState();
			break;
		default:
			// program should not reach here
			break;
	} // end switch statement

}

void q_learning::learn() {
	if(!firstPass) {
		double Q = getQ(current_state,action);
		double value = Q + ALPHA * (reward() + GAMMA * maxQ(current_state) - Q);

    	updateQ(current_state, action, value);

    	current_state = next_state;
	} else {
		firstPass = false;
	}

	do {
		action = *(actions[current_state]+rand()%LENGTH); //choose next state
		printf("Action: %d\n", action);
	} while(action == -1);
	next_state = action;

	printf("Next State: %d\n", next_state);

	//change TTT and hys
	changeTTThys();

	send_delay(new event(LEARN),180);
}

double q_learning::maxQ(int state) {
	int* nextstates = actions[state];
	double maxq = -999999;
	double q = 0.0;
	for(int i=0; i<LENGTH; i++) {
		if(*(nextstates+i) != -1) {
            q = Q[state][*(nextstates+i)];
            if (q > maxq)
                maxq = q;
		}
	}
	return maxq;
}

double q_learning::getQ(int state, int action) {
	return Q[state][action];
}

void q_learning::updateQ(int state, int action, double q) {
	Q[state][action] = q;
}

double q_learning::reward() {
	double reward = 0.0;
	reward = rewardHandover[id]-(10*rewardDrop[id] + 2*rewardPing[id]);
	rewardDrop[id] = 0;
	rewardHandover[id] = 0;
	rewardPing[id] = 0;
	return reward;
}

void q_learning::changeTTThys() {
	if(next_state >= 0 && next_state < 21) {
		TTTindex[id] = 0;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-0;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 21 && next_state < 42) {
		TTTindex[id] = 1;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-21;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 42 && next_state < 63) {
		TTTindex[id] = 2;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-42;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 63 && next_state < 84) {
		TTTindex[id] = 3;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-63;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 84 && next_state < 105) {
		TTTindex[id] = 4;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-84;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 105 && next_state < 126) {
		TTTindex[id] = 5;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-105;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 126 && next_state < 147) {
		TTTindex[id] = 6;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-126;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 147 && next_state < 168) {
		TTTindex[id] = 7;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-147;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 168 && next_state < 189) {
		TTTindex[id] = 8;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-168;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 189 && next_state < 210) {
		TTTindex[id] = 9;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-189;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 210 && next_state < 231) {
		TTTindex[id] = 10;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-210;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 231 && next_state < 252) {
		TTTindex[id] = 11;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-231;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 252 && next_state < 273) {
		TTTindex[id] = 12;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-252;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 273 && next_state < 294) {
		TTTindex[id] = 13;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-273;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 294 && next_state < 315) {
		TTTindex[id] = 14;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-294;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 315 && next_state < 336) {
		TTTindex[id] = 15;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-315;
		hys[id] = hysArray[hysindex[id]];
	}
	// printf("Learner: %d State: %d - New: TTT: %f hys: %f\n", id,next_state,TTT[id],hys[id]);
}

void q_learning::changeState() {
	next_state = policyArray[current_state];

	double Q = getQ(current_state,action);
	double value = Q + ALPHA * (reward() + GAMMA * maxQ(current_state) - Q);

    updateQ(current_state, action, value);

    int updatePolicy = policy(current_state);
    policyArray[current_state] = updatePolicy;

	changeTTThys();
	current_state = next_state;
}

void q_learning::print() {
	// for(int i=0; i<NUMSTATES; i++) {
	// 	for(int j=0; j<NUMSTATES; j++) {
	// 		printf("%f ", Q[i][j]);
	// 	}
	// 	printf("\n");
	// }
	printPolicy();

	//print Q to file
	std::ofstream qFile (qString);
	if (qFile.is_open()) {
		for(int i=0; i<NUMSTATES; i++) {
			for(int j=0; j<NUMSTATES; j++) {
    			qFile << Q[i][j] << "\n";
  			}
  		}
  	}

  	qFile.close();
}

int q_learning::policy(int current) {
    double maxValue = -99999;
    int maxNext = -1; // For testing cause not all Q's have values yet
    for (int i = 0; i < LENGTH; i++) {
        int nextState = *(actions[current]+i);

        if(nextState != -1) {
          	double value = getQ(current,nextState);
 
           	if (value > maxValue) {
               	maxValue = value;
           	    maxNext = nextState;
           	}
       	}
    }
    // printf("State: %d Value: %f\n",current,maxValue);
    return maxNext;
}

void q_learning::printPolicy() {
	std::ofstream pFile (policyString);

	if(pFile.is_open()) {
    	for (int i=0; i < NUMSTATES; i++) {
    	    int current = i;
    	    int next =  policy(current);
    	    pFile << next << "\n";
    	    printf("From %d Next %d\n",current,next);
    	}    
    } 
    pFile.close();      
}