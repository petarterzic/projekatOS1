#include "MainTh.h";
#include<iostream.h>;
#include "PCB.h"

extern int userMain(int, char* argv[]);
//extern int userMain();

extern PCB *mainPCB;
MainThread::MainThread(int argc_, char *argv_[]) :
		Thread(4096, 0) {
	argc = argc_;
	argv = argv_;
}

MainThread::~MainThread() {
	waitToComplete();
}

void MainThread::run() {
	userMain(argc, argv);
	//cout<<(PCB::runningPCB->id);
	//userMain();
}
