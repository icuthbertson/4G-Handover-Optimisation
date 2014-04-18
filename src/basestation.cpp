#include "bstations.h"
#include <stdio.h>
#include <math.h>
#include "event_definitions.h"
#include "mobiles.h"
#include "prop.h"
#include "q.h"
#include <random>

std::default_random_engine generator;
//std::normal_distribution<double> distribution(0.0,6.0);
//Comment in the above line if using fading.

/* Constructor
 ****************************
 * Return Type: N/A
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Basic class constructor that create an instance of basestation
 * with all parameters set to zero. Inheritance from the event_handler
 * abstract class is also instantiated. This should never be used.
 */
basestation::basestation(scheduler* gs) : event_handler(gs) {
    id = 0; //ID for this base station.
	x_co = 0; //X-Co-Ordinate for this base station.
	y_co = 0; //Y-Co_ordinate for this base station.
	f = 0.0; //Frequency of this base station.
	hb = 0.0; //Height of this base station.
	for(int i=0; i<NUM_MOBILES; i++) {
    	connected[i] = false; //set for no connection currently.
    }
	tx = 46.0; //Transmit power of the base station.
}
/* Constructor
 ****************************
 * Return Type: N/A
 ****************************
 * Parameters Passed in:
 * schedular* gs
 * int idNum
 * int x
 * int y
 * double freq
 * double hBase
 ****************************
 * Description: Class constructor that create an instance of basestation
 * with all parameters are passed in. Inheritance from the event_handler
 * abstract class is also instantiated.
 */
basestation::basestation(scheduler* gs, int idNum, int x, int y, double freq, double hBase) : event_handler(gs) {
	id = idNum; //ID for this base station.
    x_co = x; //X-Co-Ordinate for this base station.
    y_co = y; //Y-Co_ordinate for this base station.
    f = freq; //Frequency of this base station.
    hb = hBase; //Height of this base station.
    for(int i=0; i<NUM_MOBILES; i++) {
    	connected[i] = false; //set for no connection currently.
    }
    tx = 46.0; //Transmit power of the base station.
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
            //Event so the information for this base station can be displayed.
			print();
			break;
		case PROP:
            //Set of classes for payloads passed with the event.
            //Set up prop variable as well.
			propRequestPacket* recPacket;
			double prop;
			propSendPacket* sendPacket;

            //Get the attachment/payload of the event.
			recPacket = reinterpret_cast<propRequestPacket*>(received->getAttachment());

            //Calculate the path loss with the distance and mobile height from
            //the payload.
			prop = getProp(recPacket->dist,recPacket->height);

            //Create the payload to return to the mobile and send it now so that
            //it functions as if the mobile was taking signal strength reading
            //itself.
			sendPacket = new propSendPacket(id,prop);
			send_now(new event(PROP,reinterpret_cast<payloadType<class T>*>(sendPacket), received->sender));
			//printf("Basestation: %d\n",id);
			delete recPacket;
			break;
		case REPORT:
            //Set of classes for payloads passed with the event.
			reportPacket* repPacket;
			repPacket = reinterpret_cast<reportPacket*>(received->getAttachment());

            //Test if the mobile that sent the measurement report to this base
            //station is still handing over (therefore not dropped).
            //If so initiate handover. This is done assuming all base stations
            //have enough resources to accomodate all the mobiles in the simulation.
			if(handingOver[repPacket->id_mob]) {
                //Tell the neighbouring base station it is now the serving
                //base station. Not done with the DES framework for speed of
                //computation.
				bStations[repPacket->id_base]->nowServing(repPacket->id_mob);
                //Set this base station to no longer be the serving bse station.
                //Not done with the DES framework for speed of computation.
				this->connected[repPacket->id_mob] = false;
                //Tell the mobile to swtich to being connected to the neighbouring
                //base station.
                //Not done with the DES framework for speed of computation.
				mobiles[repPacket->id_mob]->switchBasestation(repPacket->id_base);
                //Increment the number of successful handover and reward counter
                //for this base station.
				handovers[repPacket->id_base]++;
				rewardHandover[repPacket->id_base]++;
                //Push the sim time for the handover to the handover vector for
                //this base station.
				handover_total[repPacket->id_base].push_back(simTime[repPacket->id_mob]);
                //Set the handingOver variable for the mobile to false. Not handing
                //over anymore.
				handingOver[repPacket->id_mob] = false;
                //Set up pingpong packet to be sent with the id of the mobile
                //that was just handed over to the neighbouring base station.
				pingpongPacket* sendPacket;
				sendPacket = new pingpongPacket(repPacket->id_mob);
                //Send ping-pong packets to this base station for every time
                //step in the 5 second window for a ping-pong to occur.
				for(int j=0; j<(T_CRIT/STEPTIME); j++) {
					send_delay(new event(PINGPONG,reinterpret_cast<payloadType<class T>*>(sendPacket)),STEPTIME*j);
				}
			}
			delete repPacket;
			break;
		case PINGPONG:
            //Set of classes for payloads passed with the event.
			pingpongPacket* pingPacket;
			pingPacket = reinterpret_cast<pingpongPacket*>(received->getAttachment());
            //Check if this base station is connceted to the mobile with the id
            //in the payload.
			if(connected[pingPacket->id]) {
				printf("Sim Time: %f - PINGPONG! - Basestation: %d\n",simTime[pingPacket->id],id);
                //Increment the number of ping-pong and reward counter
                //for this base station.
				pingpongCount[this->id]++;
				rewardPing[this->id]++;
                //Push the sim time for the ping-pong to the ping-pong vector for
                //this base station.
				pingpong_total[this->id].push_back(simTime[pingPacket->id]);
                //Send an event to the Q-Learning agent for this base station
                //telling it a ping-pong just occured.
				if(function == 2) {
					send_now(new event(POLICY,q[this->id]));
				}
			}
			break;
			delete pingPacket;
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
    fprintf(stdout, "\nBasestation ID: %d - Final Report\nHandovers: %d\nDropped: %d\nPing-Pong: %d\n", id,handovers[id],drop[id],pingpongCount[id]);
	fprintf(stdout, "Final TTT: %f Final hys: %f\n", TTT[id],hys[id]);
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

    //Comment in the 2 lines below as well as the part of the equation if
    //using fading
    //double fading = 0.0;
    //fading = distribution(generator);

	return (tx-prop/*+fading*/);
}
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in: id
 ****************************
 * Description: Method that sets the index in the connected array to true for
 * the id of the mobile passed in.
 */
void basestation::nowServing(int id) {
	connected[id] = true;
}
