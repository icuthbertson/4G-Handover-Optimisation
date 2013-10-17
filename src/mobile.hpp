class mobile {
public:
	int id;
    int x_co;
    int y_co;
    double rx;

    mobile() {
    	id = 0;
    	x_co = 0;
    	y_co = 0;
    	rx = 0.0;
    }
    mobile(int num, int x, int y, double r) {
    	id = num;
        x_co = x;
        y_co = y;
        rx = r;
    }
    // void print();
    void print() {
    	printf("Mobile %d\nX Co-ordinate: %d\nY Co-ordinate: %d\nReceive Signal: %f\n\n", id, x_co, y_co, rx);
	}

	void setmobile(int num, int x, int y, double r) {
		id = num;
        x_co = x;
        y_co = y;
        rx = r;
	}
};
