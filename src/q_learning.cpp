#include "actions.h"
#include "prop.h"
#include "event_definitions.h"
#include <random>
#include <fstream>

q_learning::q_learning(scheduler* gs, int TTT, int hys) : event_handler(gs) {
	int startState = (TTT*20)+hys;
	if(function == 1) { //for creating policy
		int q = 0;
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

		current_state = startState;
		action = 0;
		next_state = 0;
		firstPass = true;

		send_delay(new event(LEARN),60);
	} else if(function == 2) { //for using policy
		std::cout << "here";
		std::ifstream pFile ("policy.txt");

		if(pFile.is_open()) {
			for(int i=0; i<NUMSTATES; i++) {
				pFile >> policyArray[i];
			}
		}

		current_state = startState;
	}
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
	if(next_state >= 0 && next_state < 21) {
		TTT = TTTArray[0];
		hys = hysArray[next_state-0];
	} else if(next_state >= 21 && next_state < 42) {
		TTT = TTTArray[1];
		hys = hysArray[next_state-21];
	} else if(next_state >= 42 && next_state < 63) {
		TTT = TTTArray[2];
		hys = hysArray[next_state-42];
	} else if(next_state >= 63 && next_state < 84) {
		TTT = TTTArray[3];
		hys = hysArray[next_state-63];
	} else if(next_state >= 84 && next_state < 105) {
		TTT = TTTArray[4];
		hys = hysArray[next_state-84];
	} else if(next_state >= 105 && next_state < 126) {
		TTT = TTTArray[5];
		hys = hysArray[next_state-105];
	} else if(next_state >= 126 && next_state < 147) {
		TTT = TTTArray[6];
		hys = hysArray[next_state-126];
	} else if(next_state >= 147 && next_state < 168) {
		TTT = TTTArray[7];
		hys = hysArray[next_state-147];
	} else if(next_state >= 168 && next_state < 189) {
		TTT = TTTArray[8];
		hys = hysArray[next_state-168];
	} else if(next_state >= 189 && next_state < 210) {
		TTT = TTTArray[9];
		hys = hysArray[next_state-189];
	} else if(next_state >= 210 && next_state < 231) {
		TTT = TTTArray[10];
		hys = hysArray[next_state-210];
	} else if(next_state >= 231 && next_state < 252) {
		TTT = TTTArray[11];
		hys = hysArray[next_state-231];
	} else if(next_state >= 252 && next_state < 273) {
		TTT = TTTArray[12];
		hys = hysArray[next_state-252];
	} else if(next_state >= 273 && next_state < 294) {
		TTT = TTTArray[13];
		hys = hysArray[next_state-273];
	} else if(next_state >= 294 && next_state < 315) {
		TTT = TTTArray[14];
		hys = hysArray[next_state-294];
	} else if(next_state >= 315 && next_state < 336) {
		TTT = TTTArray[15];
		hys = hysArray[next_state-315];
	}
	printf("New: TTT: %f hys: %f\n", TTT,hys);
}

void q_learning::changeState() {
	next_state = policyArray[current_state];
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
    return maxNext;
}

void q_learning::printPolicy() {
	std::ofstream pFile ("policy.txt");

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
