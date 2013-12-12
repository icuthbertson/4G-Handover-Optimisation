// event_handler.h: interface for the event_handler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENT_HANDLER_H__C51CAB58_13F3_4CA6_BFC5_39969B24C592__INCLUDED_)
#define AFX_EVENT_HANDLER_H__C51CAB58_13F3_4CA6_BFC5_39969B24C592__INCLUDED_



class event;
#include "scheduler.h"
#include <cassert>


// In order to make the code more efficient the event scheduler must be passed
// _explicitly_ into every object that is derived from the event_handler class.
// This marks a departure from the approach adopted by the original CNCL library
// whereby a pointer to the scheduler was passed on receiving the first event.
// In fact the internal handle to the scheduler was updated every time an event
// arrived under CNCL, given that only one scheduler should exist this approach
// was deemed inefficient and subsequently modified. Furthermore, the former
// method often resulted in much confusion for those unfamiliar with CNCL.
class event_handler {
public:
	event_handler(scheduler* gs) : globalScheduler(gs) {};
	event_handler(const event_handler& rhs) : globalScheduler(rhs.globalScheduler) {};
	virtual ~event_handler() {};
	virtual void handler(const event* received) = 0;
	void send_now(event* new_event);
	void send_delay(event* new_event, double delay_arg);
	void send_event(event* new_event); 
protected:
	double get_time() const {return globalScheduler->get_time();}	
	scheduler* globalScheduler;

};

#endif // !defined(AFX_EVENT_HANDLER_H__C51CAB58_13F3_4CA6_BFC5_39969B24C592__INCLUDED_)
