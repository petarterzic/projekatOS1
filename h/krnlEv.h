#ifndef KRNLEV_H_
#define KRNLEV_H_

#include "typedef.h"

class PCB;
class Event;

class KernelEv {
public:
	KernelEv(IVTNo id, Event* myEvent);
	void wait();
	void signal();
	~KernelEv();
private:
	IVTNo id;
	PCB *my_PCB;
	volatile int value;
	Event* myEvent;
};

#endif /* KRNLEV_H_ */
