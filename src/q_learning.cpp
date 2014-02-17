#include "q_learning.h"
#include "prop.h"
#include <random>

q_learning::q_learning(scheduler* gs, int startState) : event_handler(gs) {
	for(int i=0; i<NUMSTATES; i++) {
		for(int j=0; j<NUMSTATES; j++) {
			Q[i][j] = 0.0;
		}
	}
	state = startState;
}

q_learning::~q_learning() {
	globalScheduler->remove_from(this);
	globalScheduler->remove_to(this);
}

void q_learning::handler(const event* received)
{

	switch(received->label) {
		
		default:
			// program should not reach here
			break;
	} // end switch statement
	
}

void q_learning::learn() {
	int nextstate = 0;
	do {
		nextstate = *(actions[state]+rand()%LENGTH);
	} while(nextstate == -1);


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

void q_learning::print() {
	for(int i=0; i<NUMSTATES; i++) {
		for(int j=0; j<NUMSTATES; j++) {
			printf("%f \n", Q[i][j]);
		}
		printf("\n");
	}
}