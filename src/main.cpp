#include "timer.h"
#include "thread.h"
#include "idle.h"
#include "pcb.h"
#include <iostream.h>
#include "MainTh.h"
#include "timeLst.h"

PCB* mainPCB;
int userMain(int argc, char* argv[]);
//int userMain();

int main(int argc, char* argv[]) {
	Idle::idleThread = new Idle();
	mainPCB = new PCB();
	PCB::runningPCB = mainPCB;

	//cout<<"main"<<endl;
	inic();
	//Timer::newInt();
	MainThread *mainThread = new MainThread(argc, argv);
	mainThread->start();
	delete mainThread;
	//int x = userMain(argc, argv);
	//dispatch();
	restore();
	//cout<<"main"<<endl;
	//Timer::oldInt();
	/*

	 TimeList *t = new TimeList();

	 t->PutInList(0, 5);

	 t->ispis();
	 t->PutInList(0, 3);

	 t->ispis();
	 t->PutInList(0, 8);

	 t->ispis();
	 t->PutInList(0, 10);

	 t->ispis();
	 t->PutInList(0, 3);
	 t->ispis();
	 t->update();
	 t->ispis();
	 t->update();
	 t->ispis();
	 t->update();
	 t->ispis();*/
	return 0;
}
