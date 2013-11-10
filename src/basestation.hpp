/* Header that contains the class definition of the basestation class
 ********************************************************************
 * The basestation class is used to represent a basestaton that will
 * have other basestations near by and a mobile moving around them.
 */
class basestation {
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
     */
	int id;
    int x_co;
    int y_co;
    double tx;
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
    basestation() {
    	id = 0;
    	x_co = 0;
    	y_co = 0;
    	tx = 0.0;
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
    basestation(int idNum, int x, int y, double t) {
    	id = idNum;
        x_co = x;
        y_co = y;
        tx = t;
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
    	printf("Basestation %d\nX Co-ordinate: %d\nY Co-ordinate: %d\nTransmit Signal: %.2f\n\n", id, x_co, y_co, tx);
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
    int getID() {
        return id;
    }
    /* Method
     ****************************
     * Return Type: double
     ****************************
     * Parameters Passed in: N/A
     ****************************
     * Description: Method that returns the transmission strength from 
     * this instance of the basestation class.
     */
    double getTX() {
        return tx;
    }
};
