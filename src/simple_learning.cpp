#include "simple.h"
#include "prop.h"
#include "event_definitions.h"

simple_learning::simple_learning(scheduler* gs) : event_handler(gs) {

}

simple_learning::~simple_learning() {
	globalScheduler->remove_from(this);
	globalScheduler->remove_to(this);
}

void simple_learning::handler(const event* received) {
	switch(received->label) {
		case POLICYDROP:
			//change state depending on policy
			learn(0);
			break;
		case POLICYPING:
			learn(1);
			break;
		default:
			// program should not reach here
			break;
	} // end switch statement
}

void simple_learning::learn(int learn) {
	printf("TTT: %f - hys: %f\n", TTT,hys);
	if(learn == 0) {
		if(TTTindex-1 >= 0) {
			TTTindex -= 1;
			TTT = TTTArray[TTTindex];
		} 
		if(hysindex-1 >= 0) {
			hysindex -= 1;
			hys = hysArray[hysindex];
		}
	} else {
		if(TTTindex+1 <= TTTmaxindex) {
			TTTindex += 1;
			TTT = TTTArray[TTTindex];
		} 
		if(hysindex+1 <= hysmaxindex) {
			hysindex += 1;
			hys = hysArray[hysindex];
		}
	}
	printf("New: TTT: %f hys: %f\n", TTT,hys);
}