#include "mobile.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "event_definitions.h"
#include "bstations.h"
#include "prop.h"
#include "q.h"

/* Constructor
 ****************************
 * Return Type: N/A
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Basic class constructor that create an instance of mobile
 * with all parameters set to zero. This should never be used.
 */
mobile::mobile(scheduler* gs) : event_handler(gs) {
    id = 0; //Set the ID for this mobile
	x_co = 0; //Set the starting X-Co-Ordinates.
	y_co = 0; //Set the starting Y-Co_ordinates.
	connected = 1; //Set the id of the base station the mobile starts connectd to.
    //Tell the base station this mobile is connected to it.
    //This works even though the base stations start with no connection because
    //the base stations are initated before the mobiles.
	bStations[connected]->connected[this->id] = true;
	h = 1.0; //Set the height of the mobile.
	minusX = 1; //Initiate to 1. no need to reverse movement right now.
	minusY = 1; //Initiate to 1. no need to reverse movement right now.
    //Set all handover event triggers to false.
	trigger[0] = false;
	trigger[1] = false;
	trigger[2] = false;
	trigger[3] = false;
	trigger[4] = false;
	trigger[5] = false;
	trigger[6] = false;
	trigger[7] = false;
	trigger[8] = false;
    //Set the current RSRP from all the base stations to 0
    //Set the TTTtest array to the TTT value for those base stations.
	for(int i=0; i<NUM_BASESTATION; i++) {
		current_prop[i] = 0.0;
		TTTtest[i] = TTT[i];
	}
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
 * double r
 * int con
 * double height
 ****************************
 * Description: Class constructor that create an instance of mobile
 * with all parameters are passed in. Inheritance from the event_handler
 * abstract class is also instantiated.
 */
mobile::mobile(scheduler* gs, int num, int x, int y, int con, double height) : event_handler(gs) {
    id = num; //Set the ID for this mobile
    x_co = x; //Set the starting X-Co-Ordinates.
    y_co = y; //Set the starting Y-Co_ordinates.
    connected = con; //Set the id of the base station the mobile starts connectd to.
    //Tell the base station this mobile is connected to it.
    //This works even though the base stations start with no connection because
    //the base stations are initated before the mobiles.
    bStations[connected]->connected[this->id] = true;
    h = height; //Set the height of the mobile.
    minusX = 1; //Initiate to 1. no need to reverse movement right now.
	minusY = 1; //Initiate to 1. no need to reverse movement right now.
    //Set all handover event triggers to false.
	trigger[0] = false;
	trigger[1] = false;
	trigger[2] = false;
	trigger[3] = false;
	trigger[4] = false;
	trigger[5] = false;
	trigger[6] = false;
	trigger[7] = false;
	trigger[8] = false;
    //Set the current RSRP from all the base stations to 0
    //Set the TTTtest array to the TTT value for those base stations.
    for(int i=0; i<NUM_BASESTATION; i++) {
        current_prop[i] = 0.0;
        TTTtest[i] = TTT[i];
    }
    //send event to start the mobile moving.
	send_delay(new event(MOVE),0.0);
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
mobile::~mobile() {
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
void mobile::handler(const event* received)
{
	switch(received->label) {
		case MOVE:
			//Call method to generate new random direction
			moveRandom();
			break;
		case STEP:
			//Call method to take next step
			moveMobile();
			//Send event to this mobile to poll all the base stations
			send_now(new event(POLL));
			break;
		case POLL:
			double dist;
			//Make payload class
			propRequestPacket* sendPacket;
			//Loop for all the base stations and send them a event with payload
			//containing the dist the mobile is from it and the height of mobile.
			for(int i=0; i<NUM_BASESTATION;i++) {
				dist = sqrt(pow((bStations[i]->getX()-getX()),2.0) + pow((bStations[i]->getY()-getY()),2.0));
   				sendPacket = new propRequestPacket(dist,h);
   				send_now(new event(PROP,reinterpret_cast<payloadType<class T>*>(sendPacket),bStations[i]));
			}
			break;
		case PROP:
			//set up classes of receiving payload.
			propSendPacket* recPacket;
			recPacket = reinterpret_cast<propSendPacket*> (received->getAttachment());
			//Set the current RSRP for the base station that sent the event with the value in
			//the payload
    		current_prop[recPacket->id] = recPacket->prop;
    		//printf("Current: id:%d Rx:%f dB\nPrevious: id:%d Rx:%f dB\n",recPacket->id,current_prop[recPacket->id],
    		//check if the call with be dropped or a handover should be triggered for the base station
    		//that sent the event.
   			checkProp(recPacket->id);
   			delete recPacket;
   			break;
		case PRINT:
			print();
			break;
		default:
			// program should not reach here
			break;
	} // end switch statement
	//End the simulation after the sim time for the mobile hits the time specified.
	//all the mobiles simtimes increase at the same rate.
	//this should have been done with the scheduler time as well at the times pushed to the
	//vectors as it would have been more efficient.
	//however this way does work
	if(simTime[id] > 1000) {
		// learning->print();
		globalScheduler->stop();
	}
}

/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that does a formetted print out of all the
 * parameters of the class and performance.
 */
void mobile::print() {
    //fprintf(stdout, "\nID: %d - Final Report\nHandovers: %d\nDropped: %d\nPing-Pong: %d\n", id,handovers,drop,pingpongCount);
	//fprintf(stdout, "Final TTT: %f Final hys: %f\n", TTT[connected],hys[connected]);
}
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that does a formetted print out of the
 * x and y co-ordinates of the mobile.
 */
void mobile::printCos() {
    printf("X Co-ordinate: %f\nY Co-ordinate: %f\n\n", x_co, y_co);
}
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in:
 * int newBasestation
 ****************************
 * Description: Method that changes the basestation id that this
 * instance of the class is "connected" to.
 */
void mobile::switchBasestation(int newBasestation) {
    connected = newBasestation;
}
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in:
 * int x
 * int y
 ****************************
 * Description: Method that "moves" this instance of the class
 * by changing it's x_co and y_co small amounts; simulating steps.
 */
void mobile::moveMobile() {
	//increase the sim time for this mobile.
	simTime[this->id] += STEPTIME;
	//If the mobile will hit the right wall.
	if((x_co+(minusX*speed*STEPTIME*sin(angle*PI/180)))>6000) {
		minusX = -1; // reverse X direction
	//If the mobile will hit the left wall.
	} else if((x_co+(minusX*speed*STEPTIME*sin(angle*PI/180)))<0) {
		minusX = -1; // reverse X direction
	}
	//take step
	x_co = x_co+(minusX*speed*STEPTIME*sin(angle*PI/180));
	//If the mobile will hit the top wall
	if((y_co+(minusY*speed*STEPTIME*cos(angle*PI/180)))>6000) {
		minusY = -1; // reverse Y direction
	//If the mobile will hit the bottom wall
	} else if((y_co+(minusY*speed*STEPTIME*cos(angle*PI/180)))<0) {
		minusY = -1; // reverse Y direction
	}
	//take step
	y_co = y_co+(minusY*speed*STEPTIME*cos(angle*PI/180));
	//If the duration of the direction is finished.
	if(duration<=0) {
		send_delay(new event(MOVE),STEPTIME); //send event to generate new direction
		//print finshing location of the direction
        fprintf(stderr, "\nSim Time: %.2f - ID %d - X_Co:%.2f Y_Co:%.2f \n",simTime[id],id,x_co,y_co);

	} else {
		duration -= STEPTIME; //reduce the durction until zero.
		send_delay(new event(STEP),STEPTIME); //event to take next step
	}
	//fprintf(stderr, "x_co:%f y_co:%f\n", x_co,y_co);
}
/* Method
 ****************************
 * Return Type: double
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that returns the value of the y co-ordinate.
 */
double mobile::getX() {
	return x_co;
}
/* Method
 ****************************
 * Return Type: double
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that returns the value of the y co-ordinate.
 */
double mobile::getY() {
	return y_co;
}
/* Method
 ****************************
 * Return Type: int
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that returns the id of the mobile that
 * the mobile is currently connected to.
 */
int mobile::getConnectedTo() {
	return connected;
}
/* Method
 ****************************
 * Return Type: double
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that returns the height of the mobile.
 */
double mobile::getHeight() {
	return h;
}
/* Method
 ****************************
 * Return Type: int
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that returns a number that will define the
 * random movement the mobile will make.
 */
void mobile::moveRandom() {
	//Generate the random integer values for the angle, speed and duration.
	angle = rand()%360; //0 to 359 degrees
	speed = (rand()%3)+1; //1 to 4 m/s
	duration = (rand()%100)+100; //100 to 200s
	//Calculate the change in X and Y values
	double deltaX = duration*speed*sin(angle*PI/180);
	double deltaY = duration*speed*cos(angle*PI/180);
	//Display the random movement parameters
	fprintf(stderr, "\nSim Time: %.2f - ID %d - X_Co:%.2f Y_Co:%.2f deltaX:%.2f deltaY:%.2f\nspeed:%f duration:%f\n",simTime[id],id,x_co,y_co,deltaX,deltaY,speed,duration);
	//Make sure that the directions won't be reversed
	minusX = 1;
	minusY = 1;
	//Start the mobile taking steps
	moveMobile();
}
/* Method
 ****************************
 * Return Type: int
 ****************************
 * Parameters Passed in: id
 ****************************
 * Description: Method that simulates the mobile testing for the A3 handover event trigger
 * and call dropping.
 */
void mobile::checkProp(int id) {
	//if the id is for the current base station the mobile is connected to.
	if(id == connected) {
		//if the RSRP is less than the threshold
		if(current_prop[id]<THRESHOLD) {
			//Increment the number of drops and reward counter
            //for the base station connected to.
			drop[connected]++;
			rewardDrop[connected]++;
			//Push the sim time for the drop to the drop vector for
            //the base station. connected to.
			drop_total[connected].push_back(simTime[this->id]);
            //if a handover had been trigger
            if(handingOver[this->id]) {
            	//Push the sim time for the failure to the failure vector for
            	//the base station. connected to.
                failure_total[connected].push_back(simTime[this->id]);
            }
			printf("Sim Time: %f - ID: %d - Prop: %f - Basestation: %d\n",simTime[this->id],id,current_prop[id],id);
			fprintf(stderr, "Sim Time: %f - ID: %d - DROPPED - Basestation: %d\n",simTime[this->id],id,connected);
			//Send an event to the Q-Learning agent for this base station
            //telling it a drop just occured.
			if(function == 2) {//runnning policy
				send_now(new event(POLICY,q[connected]));
			}
			//make sure the mobile is not handing over anymore.
			handingOver[this->id] = false;
			//reset mobile
			bStations[connected]->connected[this->id] = false;
			resetMobile();
			for(int i=0; i<NUM_BASESTATION; i++) {
 				TTTtest[i] = TTT[connected];
 				trigger[i] = false;
 			}
		}
	} else {
		//if the id is not for the current base station the mobile is connected to.
		if(!handingOver[this->id]) {
			//if the A3 event has not been triggered.
			if(trigger[id] == false) {
				//If the A3 trigger was met.
 				if(current_prop[id] >= current_prop[connected]+hys[connected]) {
 					trigger[id] = true;//start the event
 					fprintf(stderr, "Sim Time: %f - %d Serving: %f\n%d Triggered: %f\n", simTime[id],connected,current_prop[connected],id,current_prop[id]);
 				}
 			//if the A3 event has been triggered
 			} else if(trigger[id] == true){
 				//this part should have been done with the DES framework.
 				//due to unsolved bugs it had to be done this way.
				if(TTTtest[id] <= 0) {// if the time for the event has finished.
					//if the neighbouring base station is still better
					if(current_prop[id] >= current_prop[connected]+hys[connected]) {
						//send measurement report
						reportPacket* sendPacket;
						sendPacket = new reportPacket(id,this->id);
						send_delay(new event(REPORT,reinterpret_cast<payloadType<class T>*>(sendPacket),bStations[connected]), HANDOVER_TIME);
						fprintf(stderr, "Sim Time: %f - ID: %d - Switch to basestation: %d\n",simTime[this->id],this->id,id);
						//stop testing other base stations 
						for(int i=0; i<NUM_BASESTATION; i++) {
							TTTtest[i] = TTT[connected];
							trigger[i] = false;
						}
						handingOver[this->id] = true;
					//if the neighbouring base station is not better anymore
					} else {
						//reset the variables for that base station
						TTTtest[id] = TTT[connected];
						trigger[id] = false;

					}
 				}
 				//reduce the duration of the event by the steptime.
 				TTTtest[id] -= STEPTIME;
 			}
		}
	}
}
/* Method
 ****************************
 * Return Type: int
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that resets the connect of the mobile.
 */
void mobile::resetMobile() {
	double highest = -300.0;
	int highestid = 0;
	//for all the base station
	for(int j=0; j<NUM_BASESTATION; j++) {
		//if the prop of the base station is greater than
		//the current highest make it the new highest.
		if(current_prop[j] > highest) {
			highest = current_prop[j];
			highestid = j;
		}
	}
	//connect to the base station with the largest RSRP.
	//this will work as there is good coverage from the base stations
	//so there shouldn't be any gaps in coverage.
	connected = highestid;
	bStations[highestid]->nowServing(this->id);
}
