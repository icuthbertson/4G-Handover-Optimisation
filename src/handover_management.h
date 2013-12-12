/* Header that contains the class definition of the handover_management class
 ********************************************************************
 * The basestation class is used to represent a basestaton that will
 * have other basestations near by and a mobile moving around them.
 */
#include <stdio.h>
#include <math.h>
#include "basestation.h"
#include "mobile.h"
class handover_management {
private:
    /* Private Variables
     ****************************
     * basestation[] bStations: array of basestations.
     * mobile[] mobiles: array of mobiles.
     */
	basestation bStations[9];
	mobile mobiles[1];
public:
    handover_management();
	void makeDecision();
	void output();
	void moveMobile(int index);
};
