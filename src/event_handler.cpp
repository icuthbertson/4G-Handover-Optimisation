// Part of Discrete Event Simulation framework.
// Given to me by Dr. Robert C. Atkinson.
// 14/11/2013
// Other than these comments the DES framework files are unchanged
//
// event_handler.cpp: implementation of the event_handler class.
//
//////////////////////////////////////////////////////////////////////

#include "event_handler.h"
//#include "verifypointer.h"
//using namespace std;
//#include <windows.h>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////




// Used by the programmer to send an event with an appropriate
// associated delay. Based on the original CNCL function.
void event_handler::send_delay(event* new_event, double delay_arg) {
	// time event will fire is current time plus delay
//	bool canread = IsBadReadPtr(new_event, sizeof(event));
//	bool canwrite = IsBadWritePtr(new_event, sizeof(event));
//	bool canreadsched = IsBadReadPtr(globalScheduler, sizeof(scheduler));
//	bool canwritesched = IsBadWritePtr(globalScheduler, sizeof(scheduler));
	new_event->time_due = get_time() + delay_arg;
	send_event(new_event); // member function
} // send_delay

// Used by programmer to send an event to be triggered
// at the current simulation time. Based on the original CNCL function.
void event_handler::send_now(event* new_event) {
	// time event will fire is current time
//	bool canread = IsBadReadPtr(new_event, sizeof(event));
//	bool canwrite = IsBadWritePtr(new_event, sizeof(event));
//	bool canreadsched = IsBadReadPtr(globalScheduler, sizeof(scheduler));
//	bool canwritesched = IsBadWritePtr(globalScheduler, sizeof(scheduler));
	new_event->time_due = get_time();
	send_event(new_event); // member function
} // send_now



// Used by the programmer to send an event to be triggered
// at a pre-specified time. Based on the original CNCL function.
// Based on the original CNCL function.
void event_handler::send_event(event* new_event) {
	// set the target and sender fields in the event
	new_event->sender = this;

//	bool canread = IsBadReadPtr(new_event, sizeof(event));
//	bool canwrite = IsBadWritePtr(new_event, sizeof(event));
//	bool canreadsched = IsBadReadPtr(globalScheduler, sizeof(scheduler));
//	bool canwritesched = IsBadWritePtr(globalScheduler, sizeof(scheduler));
	// only need to modify target to _this_ if it as not
	// already been set to a value. That is if the target
	// field is not specified at event creation then it
	// is assumed that this event handler object is its
	// destination
	if (new_event->target == 0) new_event->target = this;
	globalScheduler->add_event(new_event);

} // send_event
