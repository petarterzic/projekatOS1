#ifndef IVTEntry_H_
#define IVTEntry_H_
#include "typedef.h"

typedef void interrupt (*pInterrupt)(...);

class KernelEv;



class IVTEntry{
	private:
		pInterrupt oldRoutine;
		pInterrupt newRoutine;
		IVTNo ivtNo;
		KernelEv *event;
	public:
		static IVTEntry* ivtEntries[256];
		IVTEntry(IVTNo ivtNo_, pInterrupt newRoutine_);
		~IVTEntry();
		void setEvent(KernelEv *event_);
		void signal();
		void callOldRoutine();
};

#endif