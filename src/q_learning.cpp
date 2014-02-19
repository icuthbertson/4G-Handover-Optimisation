#include "actions.h"
#include "prop.h"
#include "event_definitions.h"
#include <random>
#include <fstream>

q_learning::q_learning(scheduler* gs, int TTT, int hys) : event_handler(gs) {
	int q;
	std::ifstream qFile ("q.txt");

	if(qFile.is_open()) {
		for(int i=0; i<NUMSTATES; i++) {
			for(int j=0; j<NUMSTATES; j++) {
				qFile>>q;
				Q[i][j] = q; //read Q in
			}
		}
	}

    qFile.close();

	int startState = (TTT*20)+hys;
	current_state = startState;
	action = 0;
	next_state = 0;
	firstPass = true;
	send_delay(new event(LEARN),60);
}

q_learning::~q_learning() {
	globalScheduler->remove_from(this);
	globalScheduler->remove_to(this);
}

void q_learning::handler(const event* received)
{

	switch(received->label) {
		case LEARN:
			printf("HERE\n");
			learn();
		default:
			// program should not reach here
			break;
	} // end switch statement
	
}

void q_learning::learn() {
	if(!firstPass) {
		double Q = getQ(current_state,action);
		double value = Q + ALPHA * (reward() + GAMMA * maxQ(current_state)) - Q;

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

	send_delay(new event(LEARN),60);
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
	reward = rewardHandover - rewardDrop - (2*rewardPing);
	rewardDrop = 0;
	rewardHandover = 0;
	rewardPing = 0;
	return reward;
}

void q_learning::changeTTThys() {
	if(next_state >= 0 && next_state < 20) {
		TTT = TTTArray[0];
		hys = hysArray[next_state-0];
	} else if(next_state >= 20 && next_state < 40) {
		TTT = TTTArray[1];
		hys = hysArray[next_state-20];
	} else if(next_state >= 40 && next_state < 60) {
		TTT = TTTArray[2];
		hys = hysArray[next_state-40];
	} else if(next_state >= 60 && next_state < 80) {
		TTT = TTTArray[3];
		hys = hysArray[next_state-60];
	} else if(next_state >= 80 && next_state < 100) {
		TTT = TTTArray[4];
		hys = hysArray[next_state-80];
	} else if(next_state >= 100 && next_state < 120) {
		TTT = TTTArray[5];
		hys = hysArray[next_state-100];
	} else if(next_state >= 120 && next_state < 140) {
		TTT = TTTArray[6];
		hys = hysArray[next_state-120];
	} else if(next_state >= 140 && next_state < 160) {
		TTT = TTTArray[7];
		hys = hysArray[next_state-140];
	} else if(next_state >= 160 && next_state < 180) {
		TTT = TTTArray[8];
		hys = hysArray[next_state-160];
	} else if(next_state >= 180 && next_state < 200) {
		TTT = TTTArray[9];
		hys = hysArray[next_state-180];
	} else if(next_state >= 200 && next_state < 220) {
		TTT = TTTArray[10];
		hys = hysArray[next_state-200];
	} else if(next_state >= 220 && next_state < 240) {
		TTT = TTTArray[11];
		hys = hysArray[next_state-220];
	} else if(next_state >= 240 && next_state < 260) {
		TTT = TTTArray[12];
		hys = hysArray[next_state-240];
	} else if(next_state >= 260 && next_state < 280) {
		TTT = TTTArray[13];
		hys = hysArray[next_state-260];
	} else if(next_state >= 280 && next_state < 300) {
		TTT = TTTArray[14];
		hys = hysArray[next_state-280];
	}
	printf("New: TTT: %f hys: %f\n", TTT,hys);
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
	std::ofstream qFile ("q.txt");
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
    int policyGotoState = current; // For testing cause not all Q's have values yet
    for (int i = 0; i < LENGTH; i++) {
        int nextState = *(actions[current]+i);

        if(nextState != -1) {	

          	double value = getQ(current,nextState);
 
           	if (value > maxValue) {
               	maxValue = value;
           	    policyGotoState = nextState;
           	}
       	}
    }
    return policyGotoState;
}

void q_learning::printPolicy() {
    for (int i=0; i < NUMSTATES; i++) {
        int current = i;
        int next =  policy(current);
        printf("From %d Next %d\n",current,next);
    }           
}
