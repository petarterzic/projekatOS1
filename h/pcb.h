/*
 * pcb.h
 *
 *  Created on: May 12, 2018
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "typedef.h"

class TimeList;
class PCBList;
class Thread;

class PCB {
public:

	static PCB* runningPCB;
	static PCBList* allPCBList; // allPCB
	static TimeList* sleepingPCBList;
	static int posID;
	int id;
	static int activeThreads;
	Time remainingTime, timeSlice;
	static PCB* idlePCB;
	Reg stackoffset;
	Reg basepointer;
	Reg stacksegment;
	int signal_wakening;

	enum State {
		ready, running, blocked, finished
	};
	State state;
	unsigned int* stack;

	~PCB();
	Thread *myThread;
	int stack_size;
	static void wrapper();

	PCBList* blockedPCB;

	friend class Thread;
	void waitToComplete();
	static void sleep(Time timeToSleep);

	PCB(Thread * myThread, StackSize stackSize, Time timeSlice);
	PCB();
};

#endif /* PCB_H_ */
