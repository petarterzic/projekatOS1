/*
 * idle.cpp
 *
 *  Created on: May 21, 2018
 *      Author: OS1
 */

#include "idle.h"
#include <iostream.h>
#include "typedef.h"
#include "fifoLst.h"
#include "pcb.h"
#include "timeLst.h"

Idle* Idle::idleThread = 0;
PCB *Idle::idlePCB = 0;

void Idle::run() {

	while (1) {

		PCB* check = Scheduler::get();

		if (check != 0) {
			Scheduler::put(check);
			dispatch();
		}

//			PCB::sleepingPCBList->ispis();
//			lock
//			cout<<"req"<<request<<endl;
//			unlock

	}

}
;

Idle::Idle() :
		Thread(4096, 1) {
//	 lock
//	 cout<<"odkomentarisano"<<endl;
//	 unlock
	idlePCB = PCB::allPCBList->removeFirst();
	PCB::idlePCB = idlePCB;
	// idlePCB = new PCB();
//	lock
//	cout << "idle " << idlePCB->id << endl;
//	unlock

}

Idle* Idle::getIdleInstance() {
	if (idleThread == 0) {
		return idleThread = new Idle();
	} else
		return idleThread;

}
