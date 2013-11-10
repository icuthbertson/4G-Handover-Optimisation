/* Header that contains the class definition of the mobile class
 ***************************************************************
 * The mobile class is used to represent a mobile phone that
 * will move around a number of basestations.
 */
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
    /* Constructor
     ****************************
     * Return Type: N/A 
     ****************************
     * Parameters Passed in: N/A
     ****************************
     * Description: Basic class constructor that create an instance of basestation
     * with all parameters set to zero.
     */
    mobile() {
    	id = 0;
    	x_co = 0;
    	y_co = 0;
    	rx = 0.0;
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
    mobile(int num, int x, int y, double r, int con) {
    	id = num;
        x_co = x;
        y_co = y;
        rx = r;
        connected = con;
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
    void print() {
    	printf("Mobile %d\nX Co-ordinate: %d\nY Co-ordinate: %d\nReceive Signal: %.2f\nConnected To Basestation: %d\n\n", id, x_co, y_co, rx, connected);
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
	void setmobile(int num, int x, int y, double r, int con) {
		id = num;
        x_co = x;
        y_co = y;
        rx = r;
        connected = con;
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
    void switchBasestation(int newBasestation) {
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
    void moveMobile(int x, int y) {
        x_co = x;
        y_co = y;
    }
};
