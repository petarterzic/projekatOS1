#ifndef MAINTH_H_
#define MAINTH_H_

#include "thread.h"

class MainThread:public Thread{
	private:
		int argc;
		char **argv;
	public:
		MainThread(int argc_,char **argv_);
		~MainThread();
		void run();
};


#endif
