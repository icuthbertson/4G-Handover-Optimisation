#if !(_PROP_H_)
#define _PROP_H_

#include <vector>

//external variables had to be used due to problems with
//defining headers so they would not be recursive.

#define NUM_BASESTATION 9 //define the number of base stations
#define NUM_MOBILES 10 //define the number of mobiles

extern double hys[NUM_BASESTATION]; //array of hys values for the base stations
extern double TTT[NUM_BASESTATION]; //array of TTT values for the base stations

extern int hysindex[]; //array of the index of the hys values for the base stations
extern int TTTindex[]; //array of the index of the TTT values for the base stations

extern int hysmaxindex; //max index of hys
extern int TTTmaxindex; //max index of TTT

extern double TTTArray[]; //array for all the TTT values
extern double hysArray[]; //array for all the hys values

extern bool handingOver[]; //array for the mobiles if they are handing over

extern int drop[]; //array for drop count for the base stations
extern int pingpongCount[]; //array for ping-pong count for the base stations
extern int handovers[]; //array for handover count for the base stations

extern int rewardDrop[]; //array for reward drop count for the base stations
extern int rewardPing[]; //array for reward ping-pong count for the base stations
extern int rewardHandover[]; //array for reward handover count for the base stations

extern double simTime[NUM_MOBILES]; //array of the simtimes of the mobiles

extern int function; //variable of the function the simulation is doing

extern std::vector<double> handover_total[]; //array of vectors for the time handovers occured for the base stations
extern std::vector<double> drop_total[]; //array of vectors for the time drops occured for the base stations
extern std::vector<double> pingpong_total[]; //array of vectors for the time ping-pongs occured for the base stations
extern std::vector<double> failure_total[]; //array of vectors for the time handover failures occured for the base stations
extern std::vector<int> stateChanges[]; //array of vectors for the state changes that occured for the base stations

#endif
