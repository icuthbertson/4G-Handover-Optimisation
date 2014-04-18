// Part of Discrete Event Simulation framework.
// Given to me by Dr. Robert C. Atkinson.
// 14/11/2013
// Other than these comments the DES framework files are unchanged
//
// scheduler.h: interface for the scheduler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCHEDULER_H__447AD4D5_AD20_4BAB_B5FF_2D955FDF0A49__INCLUDED_)
#define AFX_SCHEDULER_H__447AD4D5_AD20_4BAB_B5FF_2D955FDF0A49__INCLUDED_



#include "event.h"
#include<list>
#include<algorithm>
#include<functional>
#include<cstdlib>
#include<iostream>
//#include <windows.h>

class event_handler;

/*
This stuct requires some explanation. The event list (event_store) is stored in an
STL vector object. The sort algorithm can be applied to that vector, and uses the
"less than" operator (<) to rank the obects in that vector - lowest first.

However, we require to rank the objects in the vector according to two fields:
time_due and priority. It is trivial to overload the < operator for the event class
such that it ranks objects in this way. However, in order to produce efficient code
it is unwise to store objects in the vector directly - this will lead to enormous
memory allocation and de-allocation during the sort algorithm. The code can, therefore,
be made much more efficient if the vector does not store objects (events) but instead
stores pointers to the objects (pointers to events).

Unfortunately the < operator must take arguments of objectType and not objectType*,
but operator overloading is not possible for comparing pointers to objects.
Fortunately, the STL vector template allows the programmer to specify a function to
act as a comparison from within the sort algrithm. That function is specified in the
struct is_less_than.

*/

/*
struct is_less_than {
public:
	// overload the () operator
	bool operator()(event* inputa, event* inputb){
		// Note: it is not good practice to access members
		// of another object directly - accessor functions
		// would be preferred. But this function will be one
		// of the most frequently called, and speed of
		// execution outweighs other concerns.
		if (inputa->time_due < inputb->time_due) return true;
		else if (inputa->time_due > inputb->time_due) return false;
		else if (inputa->priority < inputb->priority) return true;
			else return false;
	} // () overload
}; // is_less_than
*/

class event_order: public std::binary_function<event*, event*, bool> {
public:
	// overload the () operator
	result_type operator()(first_argument_type inputa, second_argument_type inputb) const{
		// Note: it is not good practice to access members
		// of another object directly - accessor functions
		// would be preferred. But this function will be one
		// of the most frequently called, and speed of
		// execution outweighs other concerns.
		if (inputa->time_due < inputb->time_due) return true;
		else if (inputa->time_due > inputb->time_due) return false;
		else if (inputa->priority < inputb->priority) return true;
			else return false;
	} // () overload
}; // event_order


class sent_from : public std::binary_function<event*, event_handler*, bool>{
public:
	result_type operator()(first_argument_type ev, second_argument_type src) const {
		if(ev->sender == src) return true;
		else return false;
	} // () overload
}; // sent_from



class sent_to: public std::binary_function<event*, event_handler*, bool> {
public:
	result_type operator()(first_argument_type ev, second_argument_type dest)  const{
		if(ev->target == dest) return true;
		else return false;
	} // () overload
}; // sent_to

typedef std::list<event*> eventlist;

class scheduler {
public:
	scheduler();
	scheduler(const scheduler& rhs);
	virtual ~scheduler();
	// to keep simulation fast these fns are non virtual
	void add_event(event* new_event);
	void remove_event(event* old_event);
	event* peek_event() const;
	void remove_from(event_handler* source); // remove all events from source obj
	void remove_to(event_handler* target); // remove all events to target obj
	void start(void); // start simulation
	void stop(void); // stop simulation
	double get_time(void) const {return sim_time;} // return current sim time
private:
	void process_events(void) ;
	//event* next_event(void); // remove 1st event from list & return its pointer
	double sim_time; // holds current simulation time
	eventlist event_store; // array of event pointers
	bool stop_flag;
	void debug();

};

#endif // !defined(AFX_SCHEDULER_H__447AD4D5_AD20_4BAB_B5FF_2D955FDF0A49__INCLUDED_)
