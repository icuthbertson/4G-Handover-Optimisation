#if !defined(_event_definitions_h_)
#define _event_definitions_h_

enum{MOVE,PRINT,ID,X,Y,PROP,POLL,STEP};

class propRequestPacket {
	public:
		double dist;
		double height;
		propRequestPacket(double dist, double height) {
			this->dist = dist;
			this->height = height;
		}
};

class propSendPacket {
	public:
		int id;
		double prop;
		propSendPacket(int id, double prop) {
			this->id = id;
			this->prop = prop;
		}
};

#endif
