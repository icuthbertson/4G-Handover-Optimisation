/* Header that contains the class definition of the mobile class
 ***************************************************************
 * The mobile class is used to represent a mobile phone that
 * will move around a number of basestations.
 */

#if !defined(_MOBILE_H_)
#define _MOBILE_H_

#include "event_handler.h"
//Define the value of pi.
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
     * double speed: Used for random walk.
     * int angle: Used for random walk.
     * double duration: Used for random walk.
     * int minusX: Integer the is used to reverse the direction of movement if the
     *             mobile hits a vertical wall.
     * int minusY: Integer the is used to reverse the direction of movement if the
     *             mobile hits a horizontal wall.
     * bool trigger[9]: Boolean used to test if a handover event is triggered.
     * double current_prop[9]: Double array that holds the current RSRP of all
     *                         the base stations to this mobile.
     * double TTTtest[9]: Double array decrements a index to see if a measurement
     *                    report should be sent to the base station.
     */
	int id;
    double x_co;
    double y_co;
    double destX;
    double destY;
    int connected;
    double h;
    double speed;
    int angle;
    double duration;
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
