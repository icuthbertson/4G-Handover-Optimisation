#if !defined(_Q_LEARNING_H_)
#define _Q_LEARNING_H_

#include "event_handler.h"

#define ALPHA 0.9 //learning rate / step size
#define GAMMA 0.5 //how much possible future rewards matter
#define NUMSTATES 336
#define LENGTH 8

class q_learning : public event_handler {
private:
	int id;
	double Q[NUMSTATES][NUMSTATES];
	int policyArray[NUMSTATES];
	int current_state;
	int next_state;
	int action;
	bool firstPass;
	bool allActions;
	double maxQ(int state);
	double getQ(int state, int action);
	void updateQ(int state, int action, double q);
	double reward();
	void changeTTThys();
	void learn();
	int policy(int current);
	void changeState();
public:
	q_learning(scheduler* gs, int id, int TTT, int hys);
	~q_learning();
	void print();
	void printPolicy();
protected:
	virtual void handler(const event* received);
};

#endif