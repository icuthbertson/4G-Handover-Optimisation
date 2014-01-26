/* Header that contains the class definition of the handover_management class
 ********************************************************************
 * The basestation class is used to represent a basestaton that will
 * have other basestations near by and a mobile moving around them.
 */

#if !defined(_HANDOVER_MANAGMENT_H_)
#define _HANDOVER_MANAGEMENT_H_

#include "event_handler.h"

class handover_management : public event_handler {
private:
  
public:
    handover_management(scheduler* gs);
    ~handover_management();
	void makeDecision();
	void output();
	void moveMobile(int index);
protected:
	virtual void handler(const event* received);
};

// basestation* getBasestation(int id);
// mobile* getMobile(int id);

#endif
