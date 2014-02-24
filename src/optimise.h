#if !defined(_OPTIMISE_H_)
#define _OPTIMISE_H_

#include "event_handler.h"

class optimise : public event_handler {
private:

public:
    optimise(scheduler* gs);
    ~optimise();
    void learn();
    void print();
protected:
    virtual void handler(const event* received);
};

#endif