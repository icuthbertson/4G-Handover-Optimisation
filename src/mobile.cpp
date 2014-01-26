// #include "mobile.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
// #include "event_definitions.h"
// #include "handover_management.h"
// #include "basestation.h"
#include "globals.h"

/* Constructor
 ****************************
 * Return Type: N/A 
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Basic class constructor that create an instance of basestation
 * with all parameters set to zero.
 */
mobile::mobile(scheduler* gs) : event_handler(gs) {
    id = 0;
	x_co = 0;
	y_co = 0;
	connected = 1;
	h = 2.0;
	count = 0;
	stepTime = 0.0;
}
/* Constructor
 ****************************
 * Return Type: N/A 
 ****************************
 * Parameters Passed in: 
 * int idNum
 * int x
 * int y 
 * double r
 * int con
 ****************************
 * Description: Class constructor that create an instance of basestation
 * with all parameters are passed in.
 */
mobile::mobile(scheduler* gs, int num, int x, int y, int con, double height) : event_handler(gs) {
    id = num;
    x_co = x;
    y_co = y;
    connected = con;
    h = height;
    count = 0;
    stepTime = 0.01;
}
/* Destructor
 ****************************
 * Return Type: N/A 
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Class destrcutor that removes an instance of this class
 * from the schedular and any messages still waiting to be passed.
 */
mobile::~mobile() {
	globalScheduler->remove_from(this);
	globalScheduler->remove_to(this);
}
/* Method
 ****************************
 * Return Type: N/A 
 ****************************
 * Parameters Passed in:
 * const event* received
 ****************************
 * Description: Class hanlder that takes in a event and does the
 * required action depending on the event that was received.
 */
void mobile::handler(const event* received)
{
	switch(received->label) {
		case MOVE:
			moveRandom();
			print();
			count++;
			send_delay(new event(POLL,received->sender),1.0);
			break;
		case STEP:
			moveMobile();
			break;
		case PRINT:
			print();
			break;
		default:
			// program should not reach here
			break;
	} // end switch statement
	if(count > 50) {
		globalScheduler->stop();
	}
}

/* Method
 ****************************
 * Return Type: void
 **************************** 
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that does a formetted print out of all the
 * parameters of the class.
 */
void mobile::print() {
    printf("Mobile %d\nX Co-ordinate: %f\nY Co-ordinate: %f\nConnected To Basestation: %d\n", id, x_co, y_co, connected);
}
/* Method
 ****************************
 * Return Type: void
 **************************** 
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that does a formetted print out of the
 * x and y co-ordinates of the mobile.
 */
void mobile::printCos() {
    printf("X Co-ordinate: %f\nY Co-ordinate: %f\n\n", x_co, y_co);
}
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in:
 * int newBasestation
 ****************************
 * Description: Method that changes the basestation id that this
 * instance of the class is "connected" to.
 */
void mobile::switchBasestation(int newBasestation) {
    connected = newBasestation;
}
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in:
 * int x
 * int y
 ****************************
 * Description: Method that "moves" this instance of the class
 * by changing it's x_co and y_co variables to the values
 * passed in.
 */
void mobile::moveMobile() {
	if(duration>0) {
		if((x_co+(speed*stepTime*sin(angle)))>1500) {
			x_co = 1500;
			duration = 0;
		} else if((x_co+(speed*stepTime*sin(angle)))<0) {
			x_co = 0;
			duration = 0;
		} else {
			x_co = x_co+(speed*stepTime*sin(angle));
		}
		if((y_co+(speed*stepTime*cos(angle)))>1500) {
			y_co = 1500;
			duration = 0;
		} else if((y_co+(speed*stepTime*cos(angle)))<0) {
			y_co = 0;
			duration = 0;
		} else {
			y_co = y_co+(speed*stepTime*cos(angle));
		}
		if(duration==0) {
			send_now(new event(MOVE));
		} else {
			duration -= stepTime;
			// fprintf(stderr, "duration:%f\n", duration);
			send_delay(new event(STEP),stepTime);
		}
		fprintf(stderr, "x_co:%f y_co:%f\n", x_co,y_co);
	} else {

		send_now(new event(MOVE));
	}
}
/* Method
 ****************************
 * Return Type: double
 ****************************
 * Parameters Passed in: N/A 
 ****************************
 * Description: Method that returns the value of the y co-ordinate.
 */
double mobile::getX() {
	return x_co;
}
/* Method
 ****************************
 * Return Type: double
 ****************************
 * Parameters Passed in: N/A 
 ****************************
 * Description: Method that returns the value of the y co-ordinate.
 */
double mobile::getY() {
	return y_co;
}
/* Method
 ****************************
 * Return Type: int
 ****************************
 * Parameters Passed in: N/A 
 ****************************
 * Description: Method that returns the id of the mobile that
 * the mobile is currently connected to.
 */
int mobile::getConnectedTo() {
	return connected;
}
/* Method
 ****************************
 * Return Type: double
 ****************************
 * Parameters Passed in: N/A 
 ****************************
 * Description: Method that returns the height of the mobile.
 */
double mobile::getHeight() {
	return h;
}
/* Method
 ****************************
 * Return Type: int
 ****************************
 * Parameters Passed in: N/A 
 ****************************
 * Description: Method that returns a number that will define the
 * random movement the mobile will make.
 */
void mobile::moveRandom() {
	angle = rand()%360; //0 to 359 degrees
	speed = (rand()%4)+2; //1 to 4 m/s
	duration = (rand()%100)+50; //5 to 25s

	double deltaX = duration*speed*sin(angle);
	double deltaY = duration*speed*cos(angle);

	fprintf(stderr, "\nX_Co:%f Y_Co:%f deltaX:%f deltaY:%f\nspeed:%f duration:%f\n", x_co,y_co,deltaX,deltaY,speed,duration);
	moveMobile();
}
