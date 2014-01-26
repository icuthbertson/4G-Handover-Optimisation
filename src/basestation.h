/* Header that contains the class definition of the basestation class
 ********************************************************************
 * The basestation class is used to represent a basestaton that will
 * have other basestations near by and a mobile moving around them.
 */

#if !defined(_BASESTATION_H_)
#define _BASESTATION_H_

// #include <stdio.h>
// #include <math.h>
#include "event_handler.h"
// #include "event_definitions.h"
// #include "handover_management.h"
// #include "mobile.h"

class basestation : public event_handler {
private:
    /* Private Variables
     ****************************
     * int id: Unique interger values that indentifies this instance of the class.
     * int x_co: Integer value that denotes where of the x-axis this instance of
     *           the class is found. 
     * int y_co: Integer value that denotes where of the y-axis this instance of
     *           the class is found. 
     * double f:  Double value that denoted the frequency the transmitter transmits
     *            at in MHz.
	 * double hb: Double value that denoted the height of the base station.
     */
	int id;
    int x_co;
    int y_co;
    double f;
    double hb;
public:
    basestation(scheduler* gs);
    basestation(scheduler* gs, int idNum, int x, int y, double freq, double hBase);
    ~basestation();
    void print();
    int getID();
    int getX();
    int getY();
    double getProp(double d, double hm);
protected:
	virtual void handler(const event* received);
};

#endif
