class basestation {
public:
	int id;
    int x_co;
    int y_co;
    double tx;

    basestation() {
    	id = 0;
    	x_co = 0;
    	y_co = 0;
    	tx = 0.0;
    }
    basestation(int num, int x, int y, double t) {
    	id = num;
        x_co = x;
        y_co = y;
        tx = t;
    }
    // void print();
    void print() {
    	printf("Basestation %d\nX Co-ordinate: %d\nY Co-ordinate: %d\nTransmit Signal: %f\n\n", id, x_co, y_co, tx);
	}
};
