// Part of Discrete Event Simulation framework.
// Given to me by Dr. Robert C. Atkinson.
// 14/11/2013

#if !defined(_event_definitions_h_)
#define _event_definitions_h_

#define THRESHOLD -97.5 //define the drop threshold
#define STEPTIME 0.01 //define the step time of the simulation.
#define HANDOVER_TIME 0.25 //define the time it takes for a handover to take
#define T_CRIT 5 //define the window for the ping-pong to occur.

//define the enums for the DES events
enum{MOVE,PRINT,ID,X,Y,PROP,POLL,STEP,REPORT,SWITCH,PINGPONG,LEARN,REWARD,POLICYDROP,POLICYPING,POLICY,TTTCHECK,DROP,PING};

//define the payload class for events request a base stations for the RSRP
class propRequestPacket {
	public:
		double dist;
		double height;
		propRequestPacket(double dist, double height) {
			this->dist = dist;
			this->height = height;
		}
};
//define the payload class for events that return the RSRP from a base station
class propSendPacket {
	public:
		int id;
		double prop;
		propSendPacket(int id, double prop) {
			this->id = id;
			this->prop = prop;
		}
};
//define the payload class for events telling the serving base station to initiate a handover
class reportPacket {
	public:
		int id_base;
		int id_mob;
		reportPacket(int id_base, int id_mob) {
			this->id_base = id_base;
			this->id_mob = id_mob;
		}
};
//define the payload class for events for a base station to check for a ping-pong.
class pingpongPacket {
	public:
		int id;
		pingpongPacket(int id) {
			this->id = id;
		}
};

#endif
