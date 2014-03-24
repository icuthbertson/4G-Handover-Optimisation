#if !defined(_event_definitions_h_)
#define _event_definitions_h_

#define THRESHOLD -97.5
#define STEPTIME 0.01
#define HANDOVER_TIME 0.25
#define T_CRIT 5

enum{MOVE,PRINT,ID,X,Y,PROP,POLL,STEP,REPORT,SWITCH,PINGPONG,LEARN,REWARD,POLICYDROP,POLICYPING,POLICY,TTTCHECK,DROP,PING};

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

class reportPacket {
	public:
		int id_base;
		int id_mob;
		reportPacket(int id_base, int id_mob) {
			this->id_base = id_base;
			this->id_mob = id_mob;
		}
};

class pingpongPacket {
	public:
		int id;
		pingpongPacket(int id) {
			this->id = id;
		}
};

#endif
