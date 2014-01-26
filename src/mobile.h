/* Header that contains the class definition of the mobile class
 ***************************************************************
 * The mobile class is used to represent a mobile phone that
 * will move around a number of basestations.
 */

#if !defined(_MOBILE_H_)
#define _MOBILE_H_

// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
#include "event_handler.h"
// #include "event_definitions.h"
// #include "handover_management.h"
// #include "basestation.h"

class mobile : public event_handler {
private:
    /* Private Variables
     ****************************
     * int id: Unique interger values that indentifies this instance of the class.
     * double x_co: Double value that denotes where of the x-axis this instance of
     *           the class is found. 
     * double y_co: Double value that denotes where of the y-axis this instance of
     *           the class is found. 
     * double destX: Double that denotes the current X destination for the random walk.
     * double destY: Double that denotes the current Y destination for the random walk.
     * int connected: Integer values that denoted the id number of the basestation
     *                this instance of the class is "connected" to.
	 * double h: Double value that denoted the height of the mobile.
     * int count: Integer used to stop the simulation after a set number of steps.
     * double spetTime: Double used for timing each step.
     * double speed: Used for random walk.
     * int angle: Used for random walk.
     * double duration: Used for random walk.
     */
	int id;
    double x_co;
    double y_co;
    double destX;
    double destY;
    int connected;
    double h;
    int count;
    double stepTime;
    double speed;
    int angle;
    double duration;
public:
    mobile(scheduler* gs);
    mobile(scheduler* gs, int num, int x, int y, int con, double height);
    ~mobile();
    void print();
    void printCos();
    void switchBasestation(int newBasestation);
    void moveMobile();
    double getX();
    double getY();
    int getConnectedTo();
    double getHeight();
    void moveRandom();
protected:
	virtual void handler(const event* received);
};

#endif
