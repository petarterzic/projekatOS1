/*
 * thread.cpp
 *
 *  Created on: May 13, 2018
 *      Author: OS1
 */
#include "thread.h"
#include "pcb.h"
#include "SCHEDULE.H"
#include "timer.h"
#include "typedef.h"
#include <IOSTREAM.H>
class Timer;

Thread::Thread(StackSize stackSize, Time timeSlice) {
	myPCB = new PCB(this, stackSize, timeSlice);
}


Thread::~Thread() {
//waitToComplete();
	//	delete (myPCB);
}

void Thread::start() {
	myPCB->state = PCB::ready;
	Scheduler::put(myPCB);
}

void Thread::waitToComplete() {

	myPCB->waitToComplete();
//	lock
//	cout<<"id:" <<myPCB->id<<endl;
//	unlock
}

void Thread::sleep(Time timeToSleep) {
	PCB::sleep(timeToSleep);
}

void dispatch() {

	asm cli;
	request = 1;
	timer();
	asm sti;
}
