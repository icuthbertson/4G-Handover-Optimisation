#if !(_PROP_H_)
#define _PROP_H_

extern double current_prop[];
extern double TTTtest[];

extern double hys;
extern double TTT;

extern int hysindex;
extern int TTTindex;

extern int hysmaxindex;
extern int TTTnaxindex;

extern double TTTArray[];
extern double hysArray[];

extern bool handingOver;

extern int drop;
extern int pingpongCount;
extern int handovers;
extern int handoverFailures;
extern bool checkPingPong;

extern int previous_id;

extern bool deadzone;
extern int deadzoneRecovers;

extern double simTime;

void learn(int learn);

#endif