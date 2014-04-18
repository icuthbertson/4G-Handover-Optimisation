#include "actions.h"
#include "prop.h"
#include "event_definitions.h"
#include <random>
#include <fstream>
#include <iostream>
#include <sstream>
/* Constructor
 ****************************
 * Return Type: N/A
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Class constructor that create an instance of q-learning agent
 * with all parameters are passed in. Inheritance from the event_handler
 * abstract class is also instantiated.
 */
q_learning::q_learning(scheduler* gs, int id, int TTTindex, int hysindex) : event_handler(gs) {
	this->id = id; //set the ID for this agent
	int startState = (TTTindex*21)+hysindex; //decode the starting state from the TTT and hys indexes
	printf("Start State: %d\n",startState);

	//set path for the q-values for the agent
	std::stringstream sstmq;
	sstmq << "q_arrays/q" << id << ".txt";
	qString = sstmq.str();
	//set path for the policy for the agent
	std::stringstream sstmp;
	sstmp << "policy/policy" << id << ".txt";
	policyString = sstmp.str();

	//read in the q values
	double q = 0.0;
	std::ifstream qFile (qString);
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

	if(function == 1) {
		send_delay(new event(LEARN),180);
	} else if(function == 2) { //for using policy
		//read in the policy
		std::ifstream pFile (policyString);
		if(pFile.is_open()) {
			for(int i=0; i<NUMSTATES; i++) {
				pFile >> policyArray[i];
			}
		}
	}
}
/* Destructor
 ****************************
 * Return Type: N/A
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Class destrcutor that removes an instance of this class
 * from the schedular and any messages still waiting to be passed.
 */
q_learning::~q_learning() {
	globalScheduler->remove_from(this);
	globalScheduler->remove_to(this);
}
/* Method
 ****************************
 * Return Type: N/A
 ****************************
 * Parameters Passed in:
 * const event* received
 ****************************
 * Description: Class hanlder that takes in a event and does the
 * required action depending on the event that was received.
 */
void q_learning::handler(const event* received)
{
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
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that is used when the agent is learning the
 * environment.
 */
void q_learning::learn() {
	//if not the first pass
	if(!firstPass) {
		//get the Q values for the current state and action
		double Q = getQ(current_state,action);
		//update the Q value with the reward gained
		double value = Q + ALPHA * (reward() + GAMMA * maxQ(current_state) - Q);
		//update the Q value
    	updateQ(current_state, action, value);
    	//select the next state
    	current_state = next_state;
	} else {
		firstPass = false;
	}

	do {
		//when learning the environment chose next state randomly
		action = *(actions[current_state]+rand()%LENGTH); 
		printf("Action: %d\n", action);
	} while(action == -1);
	//when action is selected the next_state is set to that action
	next_state = action;
	printf("Next State: %d\n", next_state);
	//change TTT and hys according to the next state
	changeTTThys();
	//send an event to for 180 seconds which is the time given to states
	//to gain rewards
	send_delay(new event(LEARN),180);
}
/* Method
 ****************************
 * Return Type: double
 ****************************
 * Parameters Passed in: state
 ****************************
 * Description: Method that returns the maximum Q value of
 * all the actions for the state passed in.
 */
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
/* Method
 ****************************
 * Return Type: double
 ****************************
 * Parameters Passed in: state
 *						 action
 ****************************
 * Description: Method that returns the Q value for the state
 * and action passed in.
 */
double q_learning::getQ(int state, int action) {
	return Q[state][action];
}
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in: state
 *						 action
 *						 q
 ****************************
 * Description: Method that updates a Q values for the state
 * and action passed in.
 */
void q_learning::updateQ(int state, int action, double q) {
	Q[state][action] = q;
}
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that gets the reward for the agent.
 */
double q_learning::reward() {
	double reward = 0.0;
	//calculate the reward
	reward = rewardHandover[id]-(10*rewardDrop[id] + 2*rewardPing[id]);
	//reset the variables the rewards were in
	rewardDrop[id] = 0;
	rewardHandover[id] = 0;
	rewardPing[id] = 0;
	return reward;
}
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that decoded the new TTT and hys value
 * when the state the agent is in changes when following its policy
 * according to the next_state.
 */
void q_learning::changeTTThys() {
	if(next_state >= 0 && next_state < 21) {
		TTTindex[id] = 0;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-0;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 21 && next_state < 42) {
		TTTindex[id] = 1;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-21;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 42 && next_state < 63) {
		TTTindex[id] = 2;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-42;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 63 && next_state < 84) {
		TTTindex[id] = 3;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-63;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 84 && next_state < 105) {
		TTTindex[id] = 4;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-84;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 105 && next_state < 126) {
		TTTindex[id] = 5;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-105;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 126 && next_state < 147) {
		TTTindex[id] = 6;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-126;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 147 && next_state < 168) {
		TTTindex[id] = 7;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-147;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 168 && next_state < 189) {
		TTTindex[id] = 8;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-168;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 189 && next_state < 210) {
		TTTindex[id] = 9;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-189;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 210 && next_state < 231) {
		TTTindex[id] = 10;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-210;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 231 && next_state < 252) {
		TTTindex[id] = 11;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-231;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 252 && next_state < 273) {
		TTTindex[id] = 12;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-252;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 273 && next_state < 294) {
		TTTindex[id] = 13;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-273;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 294 && next_state < 315) {
		TTTindex[id] = 14;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-294;
		hys[id] = hysArray[hysindex[id]];
	} else if(next_state >= 315 && next_state < 336) {
		TTTindex[id] = 15;
		TTT[id] = TTTArray[TTTindex[id]];
		hysindex[id] = next_state-315;
		hys[id] = hysArray[hysindex[id]];
	}
	// printf("Learner: %d State: %d - New: TTT: %f hys: %f\n", id,next_state,TTT[id],hys[id]);
}
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that changes the state of the agent when
 * following its policy.
 */
void q_learning::changeState() {
	//get the next state from the policy
	next_state = policyArray[current_state];
	//update the q-value for the state
	double Q = getQ(current_state,action);
	double value = Q + ALPHA * (reward() + GAMMA * maxQ(current_state) - Q);
    updateQ(current_state, action, value);
    //update the policy incase it changed
    int updatePolicy = policy(current_state);
    policyArray[current_state] = updatePolicy;
    //change the TTT and hys values for the base station the agent is working
    //for according to the next_state
	changeTTThys();
	//change state.
	current_state = next_state;
	//push the state change to the vector for the agent.
	stateChanges[id].push_back(current_state);
}
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that saves the q-values for the q-learning agent
 * to an external files.
 */
void q_learning::saveQValues() {
	savePolicy();
	std::ofstream qFile (qString);
	if (qFile.is_open()) {
		for(int i=0; i<NUMSTATES; i++) {
			for(int j=0; j<NUMSTATES; j++) {
    			qFile << Q[i][j] << "\n";
  			}
  		}
  	}
  	qFile.close();
}
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in: current
 ****************************
 * Description: Method that finds the best action for a states.
 */
int q_learning::policy(int current) {
    double maxValue = -99999;
    int maxNext = -1; // For testing cause not all Q's have values yet
    for (int i = 0; i < LENGTH; i++) {
    	//go through all possible actions for the state passed in
    	//and find the actions with the best future reward
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
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that writes the policy for the agent out to an
 * external file.
 */
void q_learning::savePolicy() {
	std::ofstream pFile (policyString);
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