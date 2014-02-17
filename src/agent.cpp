#include "agent.h"
#include "event_definitions.h"

agent::agent(scheduler* gs,int stateTTT,int statehys) : event_handler(gs)  {
	current_state[0] = stateTTT; 
	current_state[1] = statehys;
	for(int i=0; i<15; i++) {
		for (int j=0; j<20; j++) {
			states[i][j] = new state(i,j);
			Q[i][j] = 0.0;
		}
	}
}

agent::~agent() {
	globalScheduler->remove_from(this);
	globalScheduler->remove_to(this);
}

void agent::handler(const event* received)
{

	switch(received->label) {
		case LEARN:

			break;
		default:
			// program should not reach here
			break;
	} // end switch statement
	
}

// int agent::findMaxQ() {
// 	for() {
		
// 	}
// }