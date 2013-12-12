#include "basestation.h"

/* Constructor
 ****************************
 * Return Type: N/A 
 ****************************
 * Parameters Passed in: N/A
 **************************** 
 * Description: Basic class constructor that create an instance of basestation
 * with all parameters set to zero.
 */
basestation::basestation() {
    id = 0;
	x_co = 0;
	y_co = 0;
	f = 0.0;
	hb = 0.0;
}
/* Constructor
 ****************************
 * Return Type: N/A 
 ****************************
 * Parameters Passed in: 
 * int idNum
 * int x
 * int y
 * double t
 ****************************
 * Description: Class constructor that create an instance of basestation
 * with all parameters are passed in.
 */
basestation::basestation(int idNum, int x, int y, double freq, double hBase) {
	id = idNum;
    x_co = x;
    y_co = y;
    f = freq;
    hb = hBase;
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
void basestation::print() {
    printf("Basestation %d\nX Co-ordinate: %d\nY Co-ordinate: %d\n\n", id, x_co, y_co);
}
/* Method
 ****************************
 * Return Type: int
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that returns the id number of the instance
 * of the class.
 */
int basestation::getID() {
    return id;
}
/* Method
 ****************************
 * Return Type: int
 ****************************
 * Parameters Passed in: N/A 
 ****************************
 * Description: Method that returns the value of the x co-ordinate.
 */ 
int basestation::getX() {
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
int basestation::getY() {
	return y_co;
}
/* Method
 ****************************
 * Return Type: int
 ****************************
 * Parameters Passed in: d, hm 
 ****************************
 * Description: Method that returns the path loss using the 
 * Okumura-Hata propagation model. d in km, hm in m.
 */
double basestation::getProp(double d, double hm) {
	double ch = 0.8 + (1.1 * log10(f) - 0.7) * hm - 1.56 * log10(f);
	return 69.55 + 26.16 * log10(f) - 13.82 * log10(hb) - ch + (44.9 - 6.55 * log10(hb)) * log10(d);
}
