#include "opt.h"
#include "prop.h"

optimise::optimise(scheduler* gs) : event_handler(gs) {

}

optimise::~optimise() {
	globalScheduler->remove_from(this);
	globalScheduler->remove_to(this);
}

void optimise::handler(const event* received)
{

	switch(received->label) {
		default:
			// program should not reach here
			break;
	} // end switch statement
	
}

void optimise::learn() {
	int bestTTTindex = 0;
	int besthysindex = 0;

	int bestTTT = -99999;
	int besthys = -99999;

	for(int i=0; i<TTTmaxindex; i++) {
		if(TTT_weighting[i] > bestTTT) {
			bestTTTindex = i;
			bestTTT = TTT_weighting[i];
		}
	}
	if((TTTindex-bestTTTindex)>0) {
		TTTindex -= 1;
		TTT = TTTArray[TTTindex];
	} else if((TTTindex-bestTTTindex)<0) {
		TTTindex += 1;
		TTT = TTTArray[TTTindex];
	} else {/* Stay with the same value */}

	for(int j=0; j<hysmaxindex; j++) {
		if(hys_weighting[j] > besthys) {
			besthysindex = j;
			besthys = hys_weighting[j];
		}
	}
	if((hysindex-besthysindex)>0) {
		hysindex -= 1;
		hys = hysArray[hysindex];
	} else if((hysindex-besthysindex)<0) {
		hysindex += 1;
		hys = hysArray[hysindex];
	} else {/* Stay with the same value */}
}

void optimise::print() {
	printf("TTT Weighting\n");
	for(int i=0; i<TTTmaxindex; i++) {
		printf("TTT: %f - %d\n", TTTArray[i],TTT_weighting[i]);
	}

	printf("Hys Weighting\n");
	for(int j=0; j<hysmaxindex; j++) {
		printf("Hys: %f - %d\n", hysArray[j],hys_weighting[j]);
	}
}
