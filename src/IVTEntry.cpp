#include "IVTEntry.h"
#include "dos.h"
#include "KrnlEv.h"

IVTEntry* IVTEntry::ivtEntries[256]={0};

IVTEntry::IVTEntry(IVTNo ivtNo_, pInterrupt newRoutine_){
	ivtNo = ivtNo_;
	newRoutine = newRoutine_;
	oldRoutine = getvect(ivtNo);
	setvect(ivtNo, newRoutine);
	event = 0;
	ivtEntries[ivtNo] = this;
}

IVTEntry::~IVTEntry(){
	setvect(ivtNo, oldRoutine);
	event = 0;
}
void IVTEntry::setEvent(KernelEv *event_){
	event = event_;
}

void IVTEntry::signal(){
	event->signal();
}

void IVTEntry::callOldRoutine(){
	oldRoutine();
}
