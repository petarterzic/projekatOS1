/*
 * timeLst.h
 *
 *  Created on: May 12, 2018
 *      Author: OS1
 */

#ifndef TIMELST_H_
#define TIMELST_H_

#include "typedef.h"

class PCB;

struct TimeListElem {
	PCB* pcb;
	Time timeToSleep;
	TimeListElem* next;
	TimeListElem(PCB* pcb, Time timeToSleep);
};

class TimeList {
public:
	TimeList();
	void PutInList(PCB* pcb, Time timeToSleep);
	void remove(PCB* pcb);
	void update();
	~TimeList();
	void ispis();

	TimeListElem* head;
};

#endif /* TIMELST_H_ */
