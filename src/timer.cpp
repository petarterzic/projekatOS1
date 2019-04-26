/*
 * timer.cpp
 *
 *  Created on: May 13, 2018
 *      Author: OS1
 */
#include <dos.h>
#include "pcb.h"
#include "timer.h"
#include "idle.h"
#include "SCHEDULE.H"
#include "timeLst.h"
#include <IOSTREAM.H>
volatile unsigned request = 0;
volatile int lockFlag;
void interrupt (*Timer::old)(...) = 0;
const int Timer::IVTE = 5;

static Reg stack_segment;
static Reg stack_pointer;
static Reg base_pointer;
extern PCB* mainPCB;

void interrupt timer(...) {
	//cout<<"t"<<endl;
	if (request == 0) {
		//cout<<"t0"<<endl;
		PCB::runningPCB->remainingTime--;
		PCB::sleepingPCBList->update();
	asm int 60;
}
if (request || PCB::runningPCB->remainingTime == 0) {
	//cout<<"t1"<<endl;
	if (!lockFlag) {
		asm {
			mov stack_segment, ss;
			mov stack_pointer, sp;
			mov base_pointer, bp;
		}

		PCB::runningPCB->stacksegment = stack_segment;
		PCB::runningPCB->stackoffset = stack_pointer;
		PCB::runningPCB->basepointer = base_pointer;

//		if (PCB::runningPCB != PCB::idlePCB)
//			cout << "timer id: " << PCB::runningPCB->id << endl;

		if ((PCB::runningPCB->state == PCB::running)
				&& (PCB::runningPCB != PCB::idlePCB)
				&& (PCB::runningPCB != mainPCB)) {
			PCB::runningPCB->state = PCB::ready;
			Scheduler::put(PCB::runningPCB);

		}

		PCB::runningPCB = Scheduler::get();

		if (PCB::runningPCB == 0) {
			PCB::runningPCB = Idle::idlePCB;
		}

		PCB::runningPCB->state = PCB::running;
		stack_segment = PCB::runningPCB->stacksegment;
		stack_pointer = PCB::runningPCB->stackoffset;
		base_pointer = PCB::runningPCB->basepointer;

		PCB::runningPCB->remainingTime = PCB::runningPCB->timeSlice;

		asm {
			mov ss, stack_segment;
			mov sp, stack_pointer;
			mov bp, base_pointer;
		}
	}
}

request = 0;
}

void inic() {
Timer::old = getvect(8);
setvect(8, timer);
setvect(60, Timer::old);
}

void restore() {
setvect(8, Timer::old);
}
