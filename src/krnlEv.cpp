#include "krnlEv.h"
#include "pcb.h"
#include "IVTEntry.h"
#include "thread.h"
#include "SCHEDULE.H"

KernelEv::KernelEv(IVTNo id1, Event* myEv) {
	id = id1;
	myEvent = myEv;
	value = 0; // Can be blocked
	my_PCB = PCB::runningPCB;
	IVTEntry::ivtEntries[id1]->setEvent(this);
}

void KernelEv::wait() {
	lock

	if (my_PCB == PCB::runningPCB && value == 0) {
		my_PCB->state = PCB::blocked;
		value = 1;
		unlock

		dispatch();
	} else
		unlock
}

void KernelEv::signal() {
	lock

	if (value == 1) {
		value = 0;
		my_PCB->state = PCB::ready;
		Scheduler::put(my_PCB);
	}

	unlock
}

KernelEv::~KernelEv() {
	delete my_PCB;
}

