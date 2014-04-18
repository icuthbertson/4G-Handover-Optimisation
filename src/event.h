// Part of Discrete Event Simulation framework.
// Given to me by Dr. Robert C. Atkinson.
// 14/11/2013
// Other than these comments the DES framework files are unchanged
//
// event.h: interface for the event class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENT_H__E580E878_67D1_4438_AF10_1DA04917D99C__INCLUDED_)
#define AFX_EVENT_H__E580E878_67D1_4438_AF10_1DA04917D99C__INCLUDED_

#include <iostream>
#include "payloadType.h"

class event_handler;

class event {
public:
	// constructors
	event(long arg_label, unsigned arg_priority = 0);
	event(long arg_label, event_handler* arg_target, unsigned arg_priority = 0);
	event(long arg_label, double arg_time, unsigned arg_priority = 0);
	event(long arg_label, event_handler* arg_target, double arg_time,
		unsigned arg_priority = 0);
	// use a template function for attaching an object to the event
	event(long arg_label, payloadType<class T>* arg_payload, unsigned arg_priority = 0,
		bool volFlag = false);
	event(long arg_label, payloadType<class T>* arg_payload, event_handler* arg_target,
		unsigned arg_priority = 0, bool volFlag = false);
	event(long arg_label, payloadType<class T>* arg_payload, double arg_time,
		unsigned arg_priority = 0, bool volFlag = false);
	event(long arg_label, payloadType<class T>* arg_payload, double arg_time,
		event_handler* arg_target, unsigned arg_priority = 0, bool volFlag = false);
	event(const event& rhs);
	virtual ~event();	// destructor
	// other functions
	payloadType<class T>* getAttachment() const {return payload;}
	bool hasAttachment() const {return payloadFlag;} // has an object been included with the event?
	// time_due and priority are accessed during the event list
	// sorting algorithm. To speed this up, I'm allowing direct
	// access to them.
	double time_due;
	unsigned priority;
	// target and sender may be accessed during event sending
	// in event_handler::send_event. To speed this up, I'm allowing direct
	// access to them.
	event_handler* target;
	event_handler* sender;
	const long label;
	static unsigned evCount;
	unsigned id;
	payloadType<class T>* payload;
	bool operator<(event& rhs);
	bool operator>(event& rhs);
private:
	bool payloadFlag; // indicates if event carries an attachment
	bool volatileFlag; // indicates if attachment is deleted when event is deleted

};

#endif // !defined(AFX_EVENT_H__E580E878_67D1_4438_AF10_1DA04917D99C__INCLUDED_)
