/* Header that contains the class definition of the mobile class
 ***************************************************************
 * The mobile class is used to represent a mobile phone that
 * will move around a number of basestations.
 */
#include <stdio.h>
class mobile {
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
     */
	int id;
    int x_co;
    int y_co;
    double rx;
    int connected;
public:
    mobile();
    mobile(int num, int x, int y, double r, int con);
    void print();
	void setmobile(int num, int x, int y, double r, int con);
    void switchBasestation(int newBasestation);
    void moveMobile(int x, int y);
    int getX();
    int getY();
    int getConnectedTo();
};
