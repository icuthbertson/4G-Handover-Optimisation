#if !defined(_Q_LEARNING_H_)
#define _Q_LEARNING_H_

#include "event_handler.h"

#define ALPHA 0.1
#define GAMMA 0.9
#define NUMSTATES 336
#define LENGTH 8

class q_learning : public event_handler {
private:
	double Qdrop[NUMSTATES][NUMSTATES];
	double Qping[NUMSTATES][NUMSTATES];
	int policy_drop[NUMSTATES];
	int policy_ping[NUMSTATES];
	int current_state;
	int next_state;
	int action;
	bool firstPass;
	double maxQ(int state, int type);
	double getDropQ(int state, int action);
	double getPingQ(int state, int action);
	void updateQ(int state, int action, double q, int type);
	double getRewardDrop();
	double getRewardPing();
	void changeTTThys();
	void learn();
	int policy(int current, int type);
	void changeState(int type);
public:
	q_learning(scheduler* gs, int TTT, int hys);
	~q_learning();
	void print();
	void printPolicy();
protected:
	virtual void handler(const event* received);
};

#endif