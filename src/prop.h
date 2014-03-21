#if !(_PROP_H_)
#define _PROP_H_

#include <vector>

extern double current_prop[];
extern double TTTtest[];

extern double hys;
extern double TTT;

extern int hysindex;
extern int TTTindex;

extern int hysmaxindex;
extern int TTTmaxindex;

extern double TTTArray[];
extern double hysArray[];

extern bool handingOver;

extern int drop;
extern int pingpongCount;
extern int handovers;

extern int rewardDrop;
extern int rewardPing;
extern int rewardHandover;

extern bool checkPingPong;

extern int previous_id;

extern int deadzoneRecovers;

extern double simTime;

extern int function;

extern std::vector<double> handover_total;
extern std::vector<double> drop_total;
extern std::vector<double> pingpong_total;

void learn(int learn);

#define NUM_BASESTATION 9

#endif