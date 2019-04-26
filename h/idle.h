#ifndef IDLE_H_
#define IDLE_H_

#include "thread.h"

class PCB;

class Idle: public Thread {
public:
	Idle();
	static Idle* idleThread;
	static PCB* idlePCB;
	static Idle* getIdleInstance();

	virtual void run();
};


#endif /* IDLE_H_ */
