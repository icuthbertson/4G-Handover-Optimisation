#if !defined(_STATE_H_)
#define _STATE_H_

#include <vector>
#include "action.h"

class state {
private:
	std::vector<action*> actions;
	double Q;
public:
	state(int TTT, int hys);
	double getMaxQ();
	void updateQ(double newQ);
	double getQ();
};

#endif