#if !defined(_SIMPLE_LEARNING_H_)
#define _SIMPLE_LEARNING_H_

#include "event_handler.h"

class simple_learning : public event_handler {
private:
	void learn(int learn);
public:
	simple_learning(scheduler* gs);
	~simple_learning();
protected:
	virtual void handler(const event* received);
};

#endif