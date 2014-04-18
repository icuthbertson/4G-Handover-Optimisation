// Part of Discrete Event Simulation framework.
// Given to me by Dr. Robert C. Atkinson.
// 14/11/2013
// Other than these comments the DES framework files are unchanged
//
// event.cpp: implementation of the event class.
//
//////////////////////////////////////////////////////////////////////


#include "event.h"
#include "event_handler.h"

unsigned event::evCount = 0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



event::event(long arg_label, event_handler* arg_target,
			 unsigned arg_priority) : label(arg_label), target(arg_target),
			 priority (arg_priority)
{
	id = evCount++;
	payloadFlag = false;
	volatileFlag = false;

}


event::event(long arg_label, unsigned arg_priority) : label(arg_label), priority(arg_priority)
{
	target = 0;
	id = evCount++;
	payloadFlag = false;
	volatileFlag = false;
	//std::cerr<< "\nEvent(" << id << ") created : " << this << "\n";

}

event::event(long arg_label, double arg_time,
			 unsigned arg_priority) : label(arg_label), time_due(arg_time),
			 priority(arg_priority)
{
	target = 0;
	id = evCount++;
	payloadFlag = false;
	volatileFlag = false;

}

event::event(long arg_label, event_handler* arg_target, double arg_time,
			 unsigned arg_priority) : label(arg_label), target(arg_target),
			 time_due(arg_time), priority(arg_priority)
{
	id = evCount++;
	payloadFlag = false;
	volatileFlag = false;
}


event::event(long arg_label, payloadType<class T>* arg_payload,
			 unsigned arg_priority, bool volFlag) : label(arg_label), payload(arg_payload),
			 priority(arg_priority), volatileFlag(volFlag)
{
	target = 0;
	payloadFlag = true;
	id = evCount++;

}

event::event(long arg_label, payloadType<class T>* arg_payload, event_handler* arg_target,
			 unsigned arg_priority, bool volFlag) : label(arg_label), payload(arg_payload),
			 target(arg_target), priority(arg_priority), volatileFlag(volFlag)
{
	payloadFlag = true;
	id = evCount++;

}

event::event(long arg_label, payloadType<class T>* arg_payload, double arg_time,
			 unsigned arg_priority, bool volFlag) : label(arg_label), payload(arg_payload),
			 time_due(arg_time), priority(arg_priority), volatileFlag(volFlag)
{
	target = 0;
	payloadFlag = true;
	id = evCount++;

}

event::event(long arg_label, payloadType<class T>* arg_payload, double arg_time,
			 event_handler* arg_target, unsigned arg_priority, bool volFlag) : label(arg_label),
			 payload(arg_payload), time_due(arg_time), target(arg_target),
			 priority(arg_priority), volatileFlag(volFlag)
{
	payloadFlag = true;
	id = evCount++;

}

event::event(const event& rhs) : label(rhs.label) {
	time_due = rhs.time_due;
	priority = rhs.priority;
	target = rhs.target;
	sender = rhs.sender;
	id = rhs.id;
	payload = rhs.payload;
	payloadFlag = rhs.payloadFlag;
	volatileFlag = rhs.volatileFlag;
} // copy ctor

event::~event()
{
	if (payloadFlag && volatileFlag) delete payload;
	//std::cerr<< "\nEvent(" << id << ") deleted : " << this << "\n";

}


bool event::operator<(event& rhs) {
	if(time_due > rhs.time_due) return false;
	else if(time_due < rhs.time_due) return true;
	else if(priority < rhs.priority) return true;
	else return false;
} // operator<

bool event::operator>(event& rhs) {
	if(time_due > rhs.time_due) return true;
	else if(time_due < rhs.time_due) return false;
	else if(priority < rhs.priority) return false;
	else return true;
} // operator>
