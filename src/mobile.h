/* Header that contains the class definition of the mobile class
 ***************************************************************
 * The mobile class is used to represent a mobile phone that
 * will move around a number of basestations.
 */

#if !defined(_MOBILE_H_)
#define _MOBILE_H_

#include "event_handler.h"

#define PI 3.14159265

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
    double speed;
    int angle;
    double duration;
    int wall;
    int minusX;
    int minusY;
    bool trigger[9];
    double current_prop[9];
    double TTTtest[9];
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
    void resetMobile();
    int getConnectedTo();
    double getHeight();
    void moveRandom();
    void checkProp(int id);
protected:
	virtual void handler(const event* received);
};

#endif
