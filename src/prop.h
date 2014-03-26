#if !(_PROP_H_)
#define _PROP_H_

#include <vector>

#define NUM_BASESTATION 9
#define NUM_MOBILES 10

extern double hys[NUM_BASESTATION];
extern double TTT[NUM_BASESTATION];

extern int hysindex[];
extern int TTTindex[];

extern int hysmaxindex;
extern int TTTmaxindex;

extern double TTTArray[];
extern double hysArray[];

extern bool handingOver[];

extern int drop[];
extern int pingpongCount[];
extern int handovers[];

extern int rewardDrop[];
extern int rewardPing[];
extern int rewardHandover[];

extern bool checkPingPong;

extern int previous_id;

extern int deadzoneRecovers;

extern double simTime[NUM_MOBILES];

extern int function;

extern std::vector<double> handover_total[];
extern std::vector<double> drop_total[];
extern std::vector<double> pingpong_total[];
extern std::vector<int> stateChanges[];

void learn(int learn);

#endif