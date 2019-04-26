#ifndef KRNLSEM_H_
#define KRNLSEM_H_

#include "typedef.h"

class PCBList;

class TimeList;

class KernelSem {
public:
	KernelSem(int init = 1);
	virtual ~KernelSem();
	virtual int wait(int toBlock);
	virtual void signal();
	int val() const;
	void valInc() {
		value++;
	}
	PCBList* blockedList;
	int value;

};

#endif /* KRNLSEM_H_ */
