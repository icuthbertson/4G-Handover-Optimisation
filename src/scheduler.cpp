// scheduler.cpp: implementation of the scheduler class.
//
//////////////////////////////////////////////////////////////////////


#include "scheduler.h"
#include "event_handler.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

scheduler::scheduler()
{
	stop_flag = false;
	sim_time = 0.0;
	//std::cerr<< "\nScheduler created : " << this << "\n";
}


scheduler::scheduler(const scheduler& rhs) {
	sim_time = rhs.sim_time;
	event_store = rhs.event_store;
	stop_flag = rhs.stop_flag;
} // copy ctor

scheduler::~scheduler() {
	//std::cerr<< "\nScheduler deleted\n";
}


// add_event stores a new event on the event list
// then re-orders the list according to time due
// then priority
void scheduler::add_event(event* new_event) {
	// add event to scheduler event list
	//std::cerr << "\nAdding event (" << new_event->id << ") to event list\n";
	if (new_event->time_due < sim_time) {
		std::cout << "\nError negative time\n";
	} // if

	// new faster way to do an ordered insertion
	event_store.insert(lower_bound(event_store.begin(), event_store.end(), new_event, event_order()), new_event);
} // add_event


// remove_event removes an event from the event list
// and also deletes that event!
// NOTE: THIS FUNCTION IS NEVER CALLED
void scheduler::remove_event(event* old_event){
	event_store.remove(old_event);
	// program should never reach here perhaps add some exception handling later
} // remove_event



// remove_to removes all events from the event list sent
// to the specified object (which must a a derived type
// of the event_handler class). The events are also deleted.
void scheduler::remove_to(event_handler* target) {
	event_store.remove_if(bind2nd(sent_to(),target));
} // remove_to


// remove_from removes all events from the event list sent
// from the specified object. The events are also deleted.
void scheduler::remove_from(event_handler* source) {
	event_store.remove_if(bind2nd(sent_from(),source));
} // remove_from


// peek_event returns the event at the top of the event list
event* scheduler::peek_event(void) const {
	return event_store.empty() ? NULL : (event_store.front());
} // peek_event



void scheduler::start(void) {
	process_events();
} // start



void scheduler::stop(void) {
	stop_flag = true;
	//std::cerr << "\nEntered stop()";
	// remove all events from the list and delete them
	std::list<event*>::iterator localIterator;
	localIterator = event_store.begin();
	// new way of emptying list
	while(localIterator != event_store.end()) {
		delete (*localIterator);
		++localIterator;
	} // while
	event_store.clear();

} // stop



// process_events runs in a continuous loop, processing
// each event in turn. With discrete event simulation, after
// an event as been processed (at a specified time) the 
// simulation clock jumps to the time that the next event
// is scheduled for. Hence the requirement to update the
// scheduler's clock in this function.
// The body of this function is based entirely on that of
// the original CNCL-based function.
void scheduler::process_events(void)  {

	event* localEvent = NULL;
	event_handler* destination = NULL;
    stop_flag = false;

	while(!event_store.empty()){
		localEvent = event_store.front( );
		sim_time = localEvent->time_due; // update scheduler's sim time
		destination = localEvent->target;
		event_store.pop_front();
		destination->handler(localEvent); // send event to destination
		delete localEvent;
		if(stop_flag) break;
	} // while
 
} // process_events


void scheduler::debug() {
	event* local_event = NULL;
	std::list<event*>::iterator localIterator = event_store.begin();
	for(localIterator = event_store.begin(); localIterator != event_store.end(); ++localIterator){
		local_event = *localIterator;
		std::cerr << "\nTime due = " << local_event->time_due << "\tAddress = "
			<< local_event << "\tPriority = " << local_event->priority
			<< "\tType = " << local_event->label << "\tFrom: " << local_event->sender << "\tTo: " << local_event->target;
	} // for
} // debug()

 



