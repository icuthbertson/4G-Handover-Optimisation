#if !defined(_event_definitions_h_)
#define _event_definitions_h_

enum{MOVE,PRINT, ID, X, Y, PROP};

class propPacket {
	public:
		int dist;
		int height;
		propPacket(int dist, int height) {
			this->dist = dist;
			this->height = height;
		}
};

class doublePacket {
	public:
		double doub;
		doublePacket(double doub) {
			this->doub = doub;
		}
};

#endif
