#ifndef EVENT_H_
#define EVENT_H_

#include "typedef.h"

class KernelEv;

#include "IVTEntry.h"

class Event {
public:
	Event(IVTNo ivtNo);
	~Event();
	void wait();
protected:
	friend class KernelEv;
	void signal(); // can call KernelEv
private:
	KernelEv* myImpl;
};

#define PREPAREENTRY(num, callold)\
void interrupt inter##num(...);\
IVTEntry ivtEntry##num(num, inter##num);\
void interrupt inter##num(...){\
	if (IVTEntry::ivtEntries[num])\
		IVTEntry::ivtEntries[num]->signal();\
	if (callold && IVTEntry::ivtEntries[num])\
		IVTEntry::ivtEntries[num]->callOldRoutine();\
}


#endif /* EVENT_H_ */
