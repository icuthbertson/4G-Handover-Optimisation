#include "state.h"

state::state(int TTT, int hys) {
	if(TTT-1 > 0) {
		actions.push_back(new action(TTT-1,hys));
	} else if(hys-1 > 0) {
		actions.push_back(new action(TTT,hys-1));
	} else if(TTT-1 > 0 && hys-1 > 0) {
		actions.push_back(new action(TTT-1,hys-1));
	} else 	if(TTT+1 < 15) {
		actions.push_back(new action(TTT+1,hys));
	} else if(hys+1 < 20) {
		actions.push_back(new action(TTT,hys+1));
	} else if(TTT+1 < 15 && hys+1 < 20) {
		actions.push_back(new action(TTT+1,hys+1));
	}
	Q = 0.0;
}

double state::getMaxQ() {

	return Q;
}

void state::updateQ (double newQ) {
	Q = newQ;
}

double state::getQ() {
	return Q;
}
