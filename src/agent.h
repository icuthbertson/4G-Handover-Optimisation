#if !defined(_AGENT_H_)
#define _AGENT_H_

#include "state.h"
#include "event_handler.h"

class agent : public event_handler {

private:
	state* states[15][20];
	double Q[15][20];
	double alpha;
	double gamma;
	int current_state[2];
public:
	agent(scheduler* gs, int stateTTT, int statehys);
	~agent();
protected:
	virtual void handler(const event* received);
};

#endif
