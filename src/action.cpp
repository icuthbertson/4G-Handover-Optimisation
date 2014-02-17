#include "action.h"

action::action(int TTT, int hys) {
	actionIndex[0] = TTT;
	actionIndex[1] = hys;
}

int action::actionTTT() {
	return actionIndex[0];
}

int action::actionhys() {
	return actionIndex[1];
}
