/* Header that contains the class definition of the mobile class
 ***************************************************************
 * The mobile class is used to represent a mobile phone that
 * will move around a number of basestations.
 */
#include <stdio.h>
#include <stdlib.h>
#include "event_handler.h"
#include "event_definitions.h"
class mobile : public event_handler {
private:
    /* Private Variables
     ****************************
     * int id: Unique interger values that indentifies this instance of the class.
     * int x_co: Integer value that denotes where of the x-axis this instance of
     *           the class is found. 
     * int y_co: Integer value that denotes where of the y-axis this instance of
     *           the class is found. 
     * double tx: Double value that denoted the signal strength being transmitted
     *            from this instance of the class.
     * int connected: Integer values that denoted the id number of the basestation
     *                this instance of the class is "connected" to.
	 * double h: Double value that denoted the height of the mobile.
     */
	int id;
    int x_co;
    int y_co;
    int connected;
    double h;
public:
    mobile(scheduler* gs);
    mobile(scheduler* gs, int num, int x, int y, int con, double height);
    void print();
    void printCos();
	void setmobile(int num, int x, int y, int con, double height);
    void switchBasestation(int newBasestation);
    void moveMobile(int x, int y);
    int getX();
    int getY();
    int getConnectedTo();
    double getHeight();
    void moveRandom();
protected:
	virtual void handler(const event* received);
};
