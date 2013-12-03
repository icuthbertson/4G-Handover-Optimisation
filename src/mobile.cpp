#include "mobile.h"

/* Constructor
 ****************************
 * Return Type: N/A 
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Basic class constructor that create an instance of basestation
 * with all parameters set to zero.
 */
mobile::mobile() {
    id = 0;
	x_co = 0;
	y_co = 0;
	connected = 1;
	h = 2.0;
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
mobile::mobile(int num, int x, int y, int con, double height) {
    id = num;
    x_co = x;
    y_co = y;
    connected = con;
    h = height;
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
    printf("Mobile %d\nX Co-ordinate: %d\nY Co-ordinate: %d\nConnected To Basestation: %d\n\n", id, x_co, y_co, connected);
}
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in:
 * int num
 * int x
 * int y
 * double r
 * int con
 ****************************
 * Description: Method that allows an instance of the class that
 * was created using the basic constructor to have it's variables
 * set.
 */
void mobile::setmobile(int num, int x, int y, int con, double height) {
	id = num;
    x_co = x;
    y_co = y;
    connected = con;
    h = height;
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
void mobile::moveMobile(int x, int y) {
    x_co += x;
    y_co += y;
}
/* Method
 ****************************
 * Return Type: int
 ****************************
 * Parameters Passed in: N/A 
 ****************************
 * Description: Method that returns the value of the y co-ordinate.
 */
int mobile::getX() {
	return x_co;
}
/* Method
 ****************************
 * Return Type: int
 ****************************
 * Parameters Passed in: N/A 
 ****************************
 * Description: Method that returns the value of the y co-ordinate.
 */
int mobile::getY() {
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