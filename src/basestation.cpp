#include "bstations.h"
#include <stdio.h>
#include <math.h>
#include "event_definitions.h"
#include "mobiles.h"
#include "prop.h"
#include "q.h"
#include "simple.h"
#include <random>

std::default_random_engine generator;
std::normal_distribution<double> distribution(0.0,6.0);

/* Constructor
 ****************************
 * Return Type: N/A 
 ****************************
 * Parameters Passed in: N/A
 **************************** 
 * Description: Basic class constructor that create an instance of basestation
 * with all parameters set to zero.
 */
basestation::basestation(scheduler* gs) : event_handler(gs) {
    id = 0;
	x_co = 0;
	y_co = 0;
	f = 0.0;
	hb = 0.0;
	connected = false;
	pingpong = false;
	pingpongTime = 0.0;
	tx = 48.0;
}
/* Constructor
 ****************************
 * Return Type: N/A 
 ****************************
 * Parameters Passed in: 
 * int idNum
 * int x
 * int y
 * double t
 ****************************
 * Description: Class constructor that create an instance of basestation
 * with all parameters are passed in.
 */
basestation::basestation(scheduler* gs, int idNum, int x, int y, double freq, double hBase, bool conn) : event_handler(gs) {
	id = idNum;
    x_co = x;
    y_co = y;
    f = freq;
    hb = hBase;
    connected = conn;
    pingpong = false;
    pingpongTime = 0.0;
    tx = 48.0;
}
/* Destructor
 ****************************
 * Return Type: N/A 
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Class destrcutor that removes an instance of this class
 * from the schedular and any messages still waiting to be passed.
 */
basestation::~basestation() {
	globalScheduler->remove_from(this);
	globalScheduler->remove_to(this);
}
/* Method
 ****************************
 * Return Type: N/A 
 ****************************
 * Parameters Passed in:
 * const event* received
 ****************************
 * Description: Class hanlder that takes in a event and does the
 * required action depending on the event that was received.
 */
void basestation::handler(const event* received)
{

	switch(received->label) {
		case PRINT:
			print();
			break;
		case PROP:
			propRequestPacket* recPacket;
			double prop;
			propSendPacket* sendPacket;

			recPacket = reinterpret_cast<propRequestPacket*>(received->getAttachment());

			prop = getProp(recPacket->dist,recPacket->height);

			sendPacket = new propSendPacket(id,prop);

			send_now(new event(PROP,reinterpret_cast<payloadType<class T>*>(sendPacket), received->sender));
			//printf("Basestation: %d\n",id);
			delete recPacket;
			break;
		case REPORT:
			reportPacket* repPacket;
			repPacket = reinterpret_cast<reportPacket*>(received->getAttachment());

			// for(int i=0; i<9; i++) {
			// 	printf("Sim Time: %f - Basestation %d: %f dbm\n",simTime,i,current_prop[i]);
			// }
			if(handingOver) {


				bStations[repPacket->id]->nowServing();
				this->connected = false;
				mobiles[0]->switchBasestation(repPacket->id);

				if(handingOver) {
					handovers++;
					rewardHandover++;
					handover_total.push_back(simTime);
				}

				handingOver = false;

				// TTT_weighting[TTTindex] += 1;
				// hys_weighting[hysindex] += 1;

				for(int j=0; j<(T_CRIT/STEPTIME); j++) {
					send_delay(new event(PINGPONG),STEPTIME*j);
				}
			}
			delete repPacket;
			break;
		case PINGPONG:
			if(connected) {
				printf("Sim Time: %f - PINGPONG! - Basestation: %d\n",simTime,id);
				pingpongCount++;
				rewardPing++;
				pingpong_total.push_back(simTime);
				for(int i=0; i<NUM_BASESTATION; i++) {
					globalScheduler->remove_to(bStations[i]);
				}
				if(function == 2) {//runnning policy
					send_now(new event(POLICY,q));
				} else if(function == 3) {
					send_now(new event(POLICYPING,simple));
				}
				// TTT_weighting[TTTindex] -= 2;
				// hys_weighting[hysindex] -= 2;
				// learning->learn(); //call machine learning
			}
			break;
		default:
			// program should not reach here
			break;
	} // end switch statement
	
}
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that does a formetted print out of all the
 * parameters of the class.
 */
void basestation::print() {
    printf("Basestation %d\nX Co-ordinate: %d\nY Co-ordinate: %d\n\n", id, x_co, y_co);
}
/* Method
 ****************************
 * Return Type: int
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that returns the id number of the instance
 * of the class.
 */
int basestation::getID() {
    return id;
}
/* Method
 ****************************
 * Return Type: int
 ****************************
 * Parameters Passed in: N/A 
 ****************************
 * Description: Method that returns the value of the x co-ordinate.
 */ 
int basestation::getX() {
	return x_co;
}
/* Method
 ****************************
 * Return Type: int
 ****************************
 * Parameters Passed in: N/A 
 ****************************
 * Description: Method that returns the value of the y co-ordinate.
 */
int basestation::getY() {
	return y_co;
}
/* Method
 ****************************
 * Return Type: int
 ****************************
 * Parameters Passed in: d, hm 
 ****************************
 * Description: Method that returns the path loss using the 
 * Cost231-Hata for urban areas propagation model. d in km, hm in m.
 */
double basestation::getProp(double d, double hm) {
	//for small or medium sized city
	double ahr = 0.8 + ((1.1 * log10(f) - 0.7) * hm) - (1.56 * log10(f));
	double prop = 46.3 + (33.9 * log10(f)) - (13.82 * log10(hb)) - ahr + ((44.9 - (6.55 * log10(hb))) * log10(d/1000)); //divide by 1000 for km
	
	// double fading = ((rand()%70)-35)/10;

	double fading = 0.0;

	fading = distribution(generator);

	return (tx-prop/*-fading*/);
}

void basestation::nowServing() {
	connected = true;
}
