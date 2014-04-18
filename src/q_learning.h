#if !defined(_Q_LEARNING_H_)
#define _Q_LEARNING_H_

#include "event_handler.h"
#include <string>

#define ALPHA 0.9 //learning rate / step size
#define GAMMA 0.5 //how much possible future rewards matter
#define NUMSTATES 336 //number of states
#define LENGTH 8 //maximum number of possible actions from a state

class q_learning : public event_handler {
private:
	    /* Private Variables
     ****************************
     * int id: Unique interger values that indentifies this instance of the class.
     * int Q[][]: 2D array that holds the q-values
     * int policyArray: array that holds the policy if the agent is following the policy
     * int current_state: holds the current state the agent is in
	 * int next_state: holds the state the agent is moving into next
     * int action: holds the action about to be done
     * bool firstPass: used to stop certain parts of code being done on the first
     *				   run through the code
     * std::string qString: used for reading in the q values from external files.
	 * std::string policyString: used for reading in the policies from external files.
     */
	int id;
	double Q[NUMSTATES][NUMSTATES];
	int policyArray[NUMSTATES];
	int current_state;
	int next_state;
	int action;
	bool firstPass;
	std::string qString;
	std::string policyString;
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
	void saveQValues();
	void savePolicy();
protected:
	virtual void handler(const event* received);
};

#endif