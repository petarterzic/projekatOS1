/*
 * pcb.cpp
 *
 *  Created on: May 12, 2018
 *      Author: OS1
 */
#include <IOSTREAM.H>
#include "pcb.h"
#include "timeLst.h"
#include "thread.h"
#include "fifoLst.h"
#include "idle.h"
#include <dos.h>
#include "SCHEDULE.H"
#include <STDIO.H>

PCB* PCB::runningPCB = 0;
PCB* PCB::idlePCB = 0;
PCBList *PCB::allPCBList = new PCBList();
TimeList *PCB::sleepingPCBList = new TimeList();
int PCB::activeThreads = 0;
int PCB::posID = 0;

PCB::PCB(Thread* myThread, StackSize stackSize = defaultStackSize,
		Time timeSlice = defaultTimeSlice) {
	id = ++posID;

//	lock
//	cout << "id:" << id << endl;
//	unlock

	stack_size = stackSize / sizeof(unsigned);
	PCB::blockedPCB = new PCBList();
	remainingTime = timeSlice;

	stack = new unsigned int[stack_size];
	stack[stack_size - 1] = 0x200;
	stack[stack_size - 2] = FP_SEG(PCB::wrapper);
	stack[stack_size - 3] = FP_OFF(PCB::wrapper);
	stack[stack_size - 12] = 0;

	stacksegment = FP_SEG(stack + stack_size - 12);
	stackoffset = FP_OFF(stack + stack_size - 12);
	basepointer = FP_SEG(stack + stack_size - 12);

	this->myThread = myThread;
	state = ready;

	PCB::allPCBList->PutInList(this);
//	lock
//	asm cli
//	cout << "***PCB konstruktor***" << endl << id << endl << "active threads: "
//	<< activeThreads << endl;
//	asm sti
//	unlock

	this->timeSlice = timeSlice;
}

PCB::PCB() {
	timeSlice = defaultTimeSlice;
	id = 0;
}

PCB::~PCB() {
	lock
	;
	//cout << "id:" << id << endl;

	PCB* del;
	while (!blockedPCB->isEmpty()) {
		PCB* unblpcb = blockedPCB->removeFirst();
		unblpcb->state = PCB::ready;
		Scheduler::put(unblpcb);
	}
	delete stack;

//	lock
//	asm cli
//	cout << "***PCB destruktor***" << endl << endl << id << endl << endl
//	<< "active threads: " << activeThreads << endl << endl;
//	asm sti
//	unlock

	PCB::allPCBList->remove(this);
	unlock
	;
}

void PCB::wrapper() {
	lock
	PCB::runningPCB->state = PCB::running;
	PCB::activeThreads++;
	unlock

	PCB::runningPCB->myThread->run();

	lock

	PCB::activeThreads--;
	runningPCB->state = PCB::finished;

	while (!runningPCB->blockedPCB->isEmpty()) {
		//cout << "iter " << PCB::runningPCB->id << endl;
		PCB* unblpcb = runningPCB->blockedPCB->removeFirst();
		unblpcb->state = PCB::ready;
		Scheduler::put(unblpcb);
	}

//	cout << "***PCB wrapper kraj***" << endl << endl << "Zavrsio "
//			<< PCB::runningPCB->id << endl << endl << "active threads: "
//			<< activeThreads << endl << endl;

	unlock

	dispatch();
}

void PCB::waitToComplete() {
//	if (state == finished) {
//
//		lock
//		cout << "Vec zavrsio " << id << endl;
//		unlock
//
//	} else {
//
//		lock
//		cout << "Nije zavrsio " << id << " " << state << endl;
//		unlock
//
//	}

	if (this == PCB::runningPCB || this->state == finished
			|| this == Idle::idlePCB || this == 0)
		return;
	lock
	runningPCB->state = blocked;
	blockedPCB->PutInList(runningPCB);
	unlock
	dispatch();
}

void PCB::sleep(Time timeToSleep) {
	lock
	runningPCB->state = blocked;
	sleepingPCBList->PutInList(runningPCB, timeToSleep);
	unlock
	dispatch();
}
