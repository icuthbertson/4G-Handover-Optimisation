#include "handover_management.h"

/* Constructor
 ****************************
 * Return Type: N/A 
 ****************************
 * Parameters Passed in: N/A
 **************************** 
 * Description: Basic class constructor that create an instance of handover_management
 */
handover_management::handover_management(scheduler* gs) : event_handler(gs) {
	bStations[0] = new basestation(gs,0,0,0,2000,80);
	bStations[1] = new basestation(gs,1,50,0,2000,50);
	bStations[2] = new basestation(gs,2,100,0,2000,70);
	bStations[3] = new basestation(gs,3,0,50,2000,75);
	bStations[4] = new basestation(gs,4,50,50,2000,55);
	bStations[5] = new basestation(gs,5,100,50,2000,65);
	bStations[6] = new basestation(gs,6,0,100,2000,60);
	bStations[7] = new basestation(gs,7,50,100,2000,85);
	bStations[8] = new basestation(gs,8,100,100,2000,75);
	prop[0] = 0.0;
	prop[1] = 0.0;
	prop[2] = 0.0;
	prop[3] = 0.0;
	prop[4] = 0.0;
	prop[5] = 0.0;
	prop[6] = 0.0;
	prop[7] = 0.0;
	prop[8] = 0.0;
	mobiles[0] = new mobile(gs,1,0,50,1,3);

	for(int i=0; i<15; i++) {
		send_delay(new event(MOVE,mobiles[0]),(i*100.0));
	}
}

handover_management::~handover_management() {
	globalScheduler->remove_from(this);
	globalScheduler->remove_to(this);
}

void handover_management::handler(const event* received)
{
	switch(received->label) {
		case PROP:
			propSendPacket* recPacket;
			recPacket = reinterpret_cast<propSendPacket*> (received->getAttachment());
    		prop[recPacket->id] = recPacket->prop;
    		printf("id:%d prop:%f\n",recPacket->id,recPacket->prop);
   			delete recPacket;
   			break;
   		case POLL:
   			propRequestPacket* sendPacket0;
   			propRequestPacket* sendPacket1;
   			propRequestPacket* sendPacket2;
   			propRequestPacket* sendPacket3;
   			propRequestPacket* sendPacket4;
			propRequestPacket* sendPacket5;
   			propRequestPacket* sendPacket6;
   			propRequestPacket* sendPacket7;
   			propRequestPacket* sendPacket8;
   			double dist;
   			double height;
   			height = mobiles[0]->getHeight();

   			dist = sqrt((abs((bStations[0]->getX()-mobiles[0]->getX()))^2) + (abs((bStations[0]->getY()-mobiles[0]->getY()))^2));
   			sendPacket0 = new propRequestPacket(dist,height);
   			dist = sqrt((abs((bStations[1]->getX()-mobiles[0]->getX()))^2) + (abs((bStations[1]->getY()-mobiles[0]->getY()))^2));
   			sendPacket1 = new propRequestPacket(dist,height);
   			dist = sqrt((abs((bStations[2]->getX()-mobiles[0]->getX()))^2) + (abs((bStations[2]->getY()-mobiles[0]->getY()))^2));
   			sendPacket2 = new propRequestPacket(dist,height);
   			dist = sqrt((abs((bStations[3]->getX()-mobiles[0]->getX()))^2) + (abs((bStations[3]->getY()-mobiles[0]->getY()))^2));
   			sendPacket3 = new propRequestPacket(dist,height);
   			dist = sqrt((abs((bStations[4]->getX()-mobiles[0]->getX()))^2) + (abs((bStations[4]->getY()-mobiles[0]->getY()))^2));
   			sendPacket4 = new propRequestPacket(dist,height);
   			dist = sqrt((abs((bStations[5]->getX()-mobiles[0]->getX()))^2) + (abs((bStations[5]->getY()-mobiles[0]->getY()))^2));
			sendPacket5 = new propRequestPacket(dist,height);
			dist = sqrt((abs((bStations[6]->getX()-mobiles[0]->getX()))^2) + (abs((bStations[6]->getY()-mobiles[0]->getY()))^2));
   			sendPacket6 = new propRequestPacket(dist,height);
   			dist = sqrt((abs((bStations[7]->getX()-mobiles[0]->getX()))^2) + (abs((bStations[7]->getY()-mobiles[0]->getY()))^2));
   			sendPacket7 = new propRequestPacket(dist,height);
   			dist = sqrt((abs((bStations[8]->getX()-mobiles[0]->getX()))^2) + (abs((bStations[8]->getY()-mobiles[0]->getY()))^2));
   			sendPacket8 = new propRequestPacket(dist,height);

   			send_delay(new event(PROP,reinterpret_cast<payloadType<class T>*>(sendPacket0),bStations[0]),1.0);
   			send_delay(new event(PROP,reinterpret_cast<payloadType<class T>*>(sendPacket1),bStations[1]),2.0);
   			send_delay(new event(PROP,reinterpret_cast<payloadType<class T>*>(sendPacket2),bStations[2]),3.0);
   			send_delay(new event(PROP,reinterpret_cast<payloadType<class T>*>(sendPacket3),bStations[3]),4.0);
   			send_delay(new event(PROP,reinterpret_cast<payloadType<class T>*>(sendPacket4),bStations[4]),5.0);
			send_delay(new event(PROP,reinterpret_cast<payloadType<class T>*>(sendPacket5),bStations[5]),6.0);
   			send_delay(new event(PROP,reinterpret_cast<payloadType<class T>*>(sendPacket6),bStations[6]),7.0);
   			send_delay(new event(PROP,reinterpret_cast<payloadType<class T>*>(sendPacket7),bStations[7]),8.0);
   			send_delay(new event(PROP,reinterpret_cast<payloadType<class T>*>(sendPacket8),bStations[8]),9.0);
		case PRINT:
			//send_now(new event(PRINT,mobiles[0]));
			//mobiles[0]->print();
			break;
		default:
			// program should not reach here
			break;
	} // end switch statement
}

/* Method
 ****************************
 * Return Type: int
 ****************************
 * Parameters Passed in: int connected
 ****************************
 * Description: Method that analysis the values it has and based on those values makes
 * 				a decision on what basestation the mobile should be connected to and
 *				if the basestation is different then the mobile is connected to the new
 *				"best" basestation.
 */
void handover_management::makeDecision() {
	// double bestProp = 50000.0;
	// double dist = 0.0;
	// double prop = 0.0;
	// double h = mobiles[0]->getHeight();
	// int connected = mobiles[0]->getConnectedTo();
	// int bestID = mobiles[0]->getConnectedTo();
	// for(int i=0; i<(sizeof(bStations)/sizeof(*bStations)); i++) {
	// 	dist = sqrt((abs((bStations[i]->getX()-mobiles[0]->getX()))^2) + (abs((bStations[i]->getY()-mobiles[0]->getY()))^2));
	// 	printf("%d: dist: %f\n",i,dist);
	// 	prop = bStations[i]->getProp(dist,h);
	// 	printf("prop: %f\n",prop);
	// 	if(prop < bestProp) {
	// 		bestProp = prop;
	// 		bestID = bStations[i]->getID();
	// 	}
	// }
	// printf("bestProp: %f\n",bestProp);
	// printf("bestID: %d\n",bestID);
	// if(connected != bestID) {
 //    	mobiles[0]->switchBasestation(bestID);
	// }
}
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that prints out all the information about
 * the mobiles and basestaions being used in the simulation.
 */
void handover_management::output() {
	mobiles[0]->print();
	for(int i=0; i<9; i++) {
		bStations[i]->print();
	}
}
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in: int index
 ****************************
 * Description: Method that calls the move method for a specified mobile.
 */
void handover_management::moveMobile(int index) {
	send_now(new event(MOVE, mobiles[0]));
}
