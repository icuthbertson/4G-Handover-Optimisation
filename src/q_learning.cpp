#include "actions.h"
#include "prop.h"
#include "event_definitions.h"
#include <random>
#include <fstream>

q_learning::q_learning(scheduler* gs, int TTT, int hys) : event_handler(gs) {
	int startState = (TTT*21)+hys;
	printf("Start State: %d\n",startState);


	double q = 0.0;
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
	allActions = false;

	if(function == 1) {
		send_delay(new event(LEARN),180);
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
	reward = rewardHandover-(10*rewardDrop + 2*rewardPing);
	rewardDrop = 0;
	rewardHandover = 0;
	rewardPing = 0;
	return reward;
}

void q_learning::changeTTThys() {
	if(next_state >= 0 && next_state < 21) {
		TTTindex = 0;
		TTT = TTTArray[TTTindex];
		hysindex = next_state-0;
		hys = hysArray[hysindex];
	} else if(next_state >= 21 && next_state < 42) {
		TTTindex = 1;
		TTT = TTTArray[TTTindex];
		hysindex = next_state-21;
		hys = hysArray[hysindex];
	} else if(next_state >= 42 && next_state < 63) {
		TTTindex = 2;
		TTT = TTTArray[TTTindex];
		hysindex = next_state-42;
		hys = hysArray[hysindex];
	} else if(next_state >= 63 && next_state < 84) {
		TTTindex = 3;
		TTT = TTTArray[TTTindex];
		hysindex = next_state-63;
		hys = hysArray[hysindex];
	} else if(next_state >= 84 && next_state < 105) {
		TTTindex = 4;
		TTT = TTTArray[TTTindex];
		hysindex = next_state-84;
		hys = hysArray[hysindex];
	} else if(next_state >= 105 && next_state < 126) {
		TTTindex = 5;
		TTT = TTTArray[TTTindex];
		hysindex = next_state-105;
		hys = hysArray[hysindex];
	} else if(next_state >= 126 && next_state < 147) {
		TTTindex = 6;
		TTT = TTTArray[TTTindex];
		hysindex = next_state-126;
		hys = hysArray[hysindex];
	} else if(next_state >= 147 && next_state < 168) {
		TTTindex = 7;
		TTT = TTTArray[TTTindex];
		hysindex = next_state-147;
		hys = hysArray[hysindex];
	} else if(next_state >= 168 && next_state < 189) {
		TTTindex = 8;
		TTT = TTTArray[TTTindex];
		hysindex = next_state-168;
		hys = hysArray[hysindex];
	} else if(next_state >= 189 && next_state < 210) {
		TTTindex = 9;
		TTT = TTTArray[TTTindex];
		hysindex = next_state-189;
		hys = hysArray[hysindex];
	} else if(next_state >= 210 && next_state < 231) {
		TTTindex = 10;
		TTT = TTTArray[TTTindex];
		hysindex = next_state-210;
		hys = hysArray[hysindex];
	} else if(next_state >= 231 && next_state < 252) {
		TTTindex = 11;
		TTT = TTTArray[TTTindex];
		hysindex = next_state-231;
		hys = hysArray[hysindex];
	} else if(next_state >= 252 && next_state < 273) {
		TTTindex = 12;
		TTT = TTTArray[TTTindex];
		hysindex = next_state-252;
		hys = hysArray[hysindex];
	} else if(next_state >= 273 && next_state < 294) {
		TTTindex = 13;
		TTT = TTTArray[TTTindex];
		hysindex = next_state-273;
		hys = hysArray[hysindex];
	} else if(next_state >= 294 && next_state < 315) {
		TTTindex = 14;
		TTT = TTTArray[TTTindex];
		hysindex = next_state-294;
		hys = hysArray[hysindex];
	} else if(next_state >= 315 && next_state < 336) {
		TTTindex = 15;
		TTT = TTTArray[TTTindex];
		hysindex = next_state-315;
		hys = hysArray[hysindex];
	}
	printf("State: %d - New: TTT: %f hys: %f\n", next_state,TTT,hys);
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
    // printf("State: %d Value: %f\n",current,maxValue);
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