/* Header that contains the class definition of the handover_management class
 ********************************************************************
 * The basestation class is used to represent a basestaton that will
 * have other basestations near by and a mobile moving around them.
 */
#include <stdio.h>
#include <math.h>
#include "basestation.h"
#include "mobile.h"
#include "event_handler.h"
#include "event_definitions.h"
class handover_management : public event_handler {
private:
    /* Private Variables
     ****************************
     * basestation bStations[]: array of basestations.
     * mobile mobiles[]: array of mobiles.
     */
	
	//basestation bStations[9] = {{gs,1,0,0,2000,80}, 
	//						  {gs,2,50,0,2000,50}, 
	//						  {gs,3,100,0,2000,70}
	//						  {gs,4,0,50,2000,75}, 
	//						  {gs,5,50,50,2000,55}, 
	//						  {gs,6,100,50,2000,65}
	//						  {gs,7,0,100,2000,60}, 
	//						  {gs,8,50,100,2000,85}, 
	//						  {gs,9,100,100,2000,75}};
	//mobile mobiles[1] = {gs,1,0,50,1,3};
	
	basestation *bStations[9];
	mobile *mobiles[1];
							  
public:
    handover_management(scheduler* gs);
	void makeDecision();
	void output();
	void moveMobile(int index);
protected:
	virtual void handler(const event* received);
};
