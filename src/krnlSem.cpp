#include "krnlSem.h"
#include "timeLst.h"
#include "pcb.h"
#include "fifoLst.h"
#include "SCHEDULE.H"
#include <iostream.h>
#include "thread.h"

KernelSem::KernelSem(int init) {
	value = init;
	blockedList = new PCBList();
}

int KernelSem::wait(int toBlock) {

	lock

	int ret = 0;

	if (--value < 0) {
		if (toBlock != 0) {
//			lock
//			cout<<"blokirao"<<endl;
//			unlock
			PCB::runningPCB->state = PCB::blocked;
			blockedList->PutInList(PCB::runningPCB);
			ret = 1;
		} else {

//			lock
//			cout<<"nijeblok"<<endl;
//			unlock
			value++;
			ret = -1;
		}

		unlock

		dispatch();
	} else
		unlock

	return ret;
}

void KernelSem::signal() {
	lock

	++value;

	if (value <= 0) {

//		lock
//		cout<<endl<<"odblokirao"<<endl;
//		unlock
		PCB* pcb = blockedList->removeFirst();
		pcb->state = PCB::ready;
		Scheduler::put(pcb);
	}

	unlock
}

KernelSem::~KernelSem() {
	delete blockedList;
}

int KernelSem::val() const {
	return value;
}
