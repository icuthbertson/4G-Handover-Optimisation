/* Header that contains the class definition of the handover_management class
 ********************************************************************
 * The basestation class is used to represent a basestaton that will
 * have other basestations near by and a mobile moving around them.
 */

#if !defined(_HANDOVER_MANAGMENT_H_)
#define _HANDOVER_MANAGEMENT_H_

// #include <stdio.h>
// #include <math.h>
// #include "mobile.h"
// #include "basestation.h"
#include "event_handler.h"
// #include "event_definitions.h"

// basestation* bStations[9];
// mobile* mobiles[1];	

class handover_management : public event_handler {
private:
    /* Private Variables
     ****************************
     * basestation bStations[]: array of basestations.
     * double prop[]: array of path loss from basestations.
     * mobile mobiles[]: array of mobiles.
     * double threshold: threshold value for call dropping.
     * double handoverTime: time it will take to complete a handover.
     */
	basestation* bStations[9];
	double prop[9];
	mobile* mobiles[1];		
	double threshold;	
	double handoverTime;	  
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
