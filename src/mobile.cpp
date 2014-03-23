#include "mobile.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "event_definitions.h"
#include "bstations.h"
#include "prop.h"
#include "q.h"
#include "simple.h"
// #include "opt.h"

/* Constructor
 ****************************
 * Return Type: N/A 
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Basic class constructor that create an instance of basestation
 * with all parameters set to zero.
 */
mobile::mobile(scheduler* gs) : event_handler(gs) {
    id = 0;
	x_co = 0;
	y_co = 0;
	connected = 1;
	h = 2.0;
	count = 0;
	wall = 0;
	minusX = 1;
	minusY = 1;
	trigger[0] = false;
	trigger[1] = false;
	trigger[2] = false;
	trigger[3] = false;
	trigger[4] = false;
	trigger[5] = false;
	trigger[6] = false;
	trigger[7] = false;
	trigger[8] = false;
	// trigger[9] = false;
}
/* Constructor
 ****************************
 * Return Type: N/A 
 ****************************
 * Parameters Passed in: 
 * int idNum
 * int x
 * int y 
 * double r
 * int con
 ****************************
 * Description: Class constructor that create an instance of basestation
 * with all parameters are passed in.
 */
mobile::mobile(scheduler* gs, int num, int x, int y, int con, double height) : event_handler(gs) {
    id = num;
    x_co = x;
    y_co = y;
    connected = con;
    h = height;
    count = 0;
    wall = 0;
    minusX = 1;
	minusY = 1;
	trigger[0] = false;
	trigger[1] = false;
	trigger[2] = false;
	trigger[3] = false;
	trigger[4] = false;
	trigger[5] = false;
	trigger[6] = false;
	trigger[7] = false;
	trigger[8] = false;
	// trigger[9] = false;
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
			moveRandom();
			print();
			count++;
			break;
		case STEP:
			moveMobile();
			send_now(new event(POLL));
			break;
		case POLL:
			double dist;
			propRequestPacket* sendPacket;
			for(int i=0; i<NUM_BASESTATION;i++) {
				dist = sqrt(pow((bStations[i]->getX()-getX()),2.0) + pow((bStations[i]->getY()-getY()),2.0));
   				sendPacket = new propRequestPacket(dist,h);
   				send_now(new event(PROP,reinterpret_cast<payloadType<class T>*>(sendPacket),bStations[i]));
			}
			break;
		case PROP:
			propSendPacket* recPacket;
			recPacket = reinterpret_cast<propSendPacket*> (received->getAttachment());
    		current_prop[recPacket->id] = recPacket->prop;
    		//printf("Current: id:%d Rx:%f dB\nPrevious: id:%d Rx:%f dB\n",recPacket->id,current_prop[recPacket->id],
    		//recPacket->id,previous_prop[recPacket->id]);
   			checkProp(recPacket->id);
   			delete recPacket;
   			break;
   // 		case TTTCHECK:
   // 		   	reportPacket* tttPacket;
			// tttPacket = reinterpret_cast<reportPacket*> (received->getAttachment());
   // 			if(current_prop[tttPacket->id] >= current_prop[connected]+hys) {
   // 				//send measurement report
			// 	reportPacket* sendPacket;
			// 	sendPacket = new reportPacket(tttPacket->id);
			// 	send_delay(new event(REPORT,reinterpret_cast<payloadType<class T>*>(sendPacket),bStations[connected]), HANDOVER_TIME);
			// 	fprintf(stderr, "Sim Time: %f - Switch to basestation: %d\n", simTime,id);
			// 	handingOver = true;
			// }
			// delete tttPacket;
   // 			break;
		case PRINT:
			print();
			break;
		default:
			// program should not reach here
			break;
	} // end switch statement
	if(simTime > 100000) {
		fprintf(stdout, "\nFinal Report\nHandovers: %d\nDropped: %d\nPing-Pong: %d\n", handovers,drop,pingpongCount);
		fprintf(stdout, "Final TTT: %f Final hys: %f\n", TTT,hys);
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
 * parameters of the class.
 */
void mobile::print() {
    printf("Sim Time: %f - Mobile %d\nX Co-ordinate: %f\nY Co-ordinate: %f\nConnected To Basestation: %d\n", simTime,id, x_co, y_co, connected);
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
 * by changing it's x_co and y_co variables to the values
 * passed in.
 */
void mobile::moveMobile() {
	simTime += STEPTIME;
	if(duration>0) {
		if((x_co+(minusX*speed*STEPTIME*sin(angle*PI/180)))>4000) {
			minusX = -1;
		} else if((x_co+(minusX*speed*STEPTIME*sin(angle*PI/180)))<0) {
			minusX = -1;
		} else {
			x_co = x_co+(minusX*speed*STEPTIME*sin(angle*PI/180));
		}
		if(wall==0) { 
			if((y_co+(minusY*speed*STEPTIME*cos(angle*PI/180)))>4000) {
				minusY = -1;
			} else if((y_co+(minusY*speed*STEPTIME*cos(angle*PI/180)))<0) {
				minusY = -1;
			} else {
				y_co = y_co+(minusY*speed*STEPTIME*cos(angle*PI/180));
			}
		}
		if(duration==0) {
			send_now(new event(MOVE));
		} else {
			duration -= STEPTIME;
			send_delay(new event(STEP),STEPTIME);
		}
		//fprintf(stderr, "x_co:%f y_co:%f\n", x_co,y_co);
	} else {
		send_delay(new event(MOVE),1.0);
	}
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
	angle = rand()%360; //0 to 359 degrees
	speed = (rand()%4)+2; //1 to 4 m/s
	duration = (rand()%100)+100; //100 to 200s
	
	double deltaX = duration*speed*sin(angle*PI/180);
	double deltaY = duration*speed*cos(angle*PI/180);
	fprintf(stderr, "\nSim Time: %f - X_Co:%f Y_Co:%f deltaX:%f deltaY:%f\nspeed:%f duration:%f\n", simTime,x_co,y_co,deltaX,deltaY,speed,duration);

	minusX = 1;
	minusY = 1;

	moveMobile();
}

void mobile::checkProp(int id) {
	if(id == connected) {
		if(current_prop[id]<THRESHOLD) {
			drop++;
			rewardDrop++;
			drop_total.push_back(simTime);
			printf("Sim Time: %f - Prop: %f - Basestation: %d\n",simTime,current_prop[id],id);
			fprintf(stderr, "Sim Time: %f - DROPPED - Basestation: %d\n",simTime,connected);
			if(function == 2) {//runnning policy
				send_now(new event(POLICY,q));
			} else if(function == 3) {
				send_now(new event(POLICYDROP,simple));
			}
			
			for(int l=0; l<NUM_BASESTATION; l++) {
				globalScheduler->remove_to(bStations[l]);
			}
			handingOver = false;
			
			//reset mobile
			bStations[connected]->connected = false;
			resetMobile();
			for(int i=0; i<NUM_BASESTATION; i++) {
 				TTTtest[i] = TTT;
 				trigger[i] = false;
 			}
		}
	} else {
		if(!handingOver) {
			if(trigger[id] == false) {
 				if(current_prop[id] >= current_prop[connected]+hys) {
 					trigger[id] = true;
 					// fprintf(stderr, "Sim Time: %f - %d Serving: %f\n%d Triggered: %f\n", simTime,connected,current_prop[connected],id,current_prop[id]);
 				}
 			} else if(trigger[id] == true){
				if(TTTtest[id] <= 0) {
					if(current_prop[id] >= current_prop[connected]+hys) {
						// fprintf(stderr, "Sim Time: %f - %d Serving: %f\n%d Triggered: %f\n", simTime,connected,current_prop[connected],id,current_prop[id]);
						//send measurement report
						reportPacket* sendPacket;
						sendPacket = new reportPacket(id);
						send_delay(new event(REPORT,reinterpret_cast<payloadType<class T>*>(sendPacket),bStations[connected]), HANDOVER_TIME);
						fprintf(stderr, "Sim Time: %f - Switch to basestation: %d\n", simTime,id);
						for(int i=0; i<NUM_BASESTATION; i++) {
							TTTtest[i] = TTT;
							trigger[i] = false;
						}
						handingOver = true;
					} else {
						TTTtest[id] = TTT;
						trigger[id] = false;

					}
 				}
 				TTTtest[id] -= STEPTIME;
 			}
		}
	}
}

// void mobile::resetMobile() {
// 	// switch(connected){
// 	// 	case 0:
// 	// 		x_co = 500.0;
// 	// 		y_co = 500.0;
// 	// 		break;
// 	// 	case 1:
// 	// 		x_co = 3750.0;
// 	// 		y_co = 0.0;
// 	// 		break;
// 	// 	case 2:
// 	// 		x_co = 6250.0;
// 	// 		y_co = 2000.0;
// 	// 		break;
// 	// 	case 3:
// 	// 		x_co = 0.0;
// 	// 		y_co = 4000.0;
// 	// 		break;
// 	// 	case 4:
// 	// 		x_co = 3000.0;
// 	// 		y_co = 3000.0;
// 	// 		break;
// 	// 	case 5:
// 	// 		x_co = 6000.0;
// 	// 		y_co = 5000.0;
// 	// 		break;
// 	// 	case 6:
// 	// 		x_co = 3000.0;
// 	// 		y_co = 6000.0;
// 	// 		break;
// 	// 	case 7:
// 	// 		x_co = 0.0;
// 	// 		y_co = 7500.0;
// 	// 		break;
// 	// 	case 8:
// 	// 		x_co = 3000.0;
// 	// 		y_co = 9000.0;
// 	// 		break;
// 	// 	case 9:
// 	// 		x_co = 6000.0;
// 	// 		y_co = 8000.0;
// 	// 	default:
// 	// 		// program should not reach here
// 	// 		break;
// 	// }

// 	switch(connected){
// 		case 0:
// 			x_co = 500.0;
// 			y_co = 500.0;
// 			break;
// 		case 1:
// 			x_co = 3000.0;
// 			y_co = 0.0;
// 			break;
// 		case 2:
// 			x_co = 5500.0;
// 			y_co = 500.0;
// 			break;
// 		case 3:
// 			x_co = 0.0;
// 			y_co = 3000.0;
// 			break;
// 		case 4:
// 			x_co = 3000.0;
// 			y_co = 3000.0;
// 			break;
// 		case 5:
// 			x_co = 6000.0;
// 			y_co = 3000.0;
// 			break;
// 		case 6:
// 			x_co = 500.0;
// 			y_co = 5500.0;
// 			break;
// 		case 7:
// 			x_co = 3000.0;
// 			y_co = 6000.0;
// 			break;
// 		case 8:
// 			x_co = 5500.0;
// 			y_co = 5500.0;
// 			break;
// 		default:
// 			// program should not reach here
// 			break;
// 	}

// 	bStations[connected]->nowServing();
// }

void mobile::resetMobile() {
	double highest = -300.0;
	int highestid = 0;
	for(int j=0; j<NUM_BASESTATION; j++) {
		if(current_prop[j] > highest) {
			highest = current_prop[j];
			highestid = j;
		}
	}
	connected = highestid;
	bStations[highestid]->nowServing();
}