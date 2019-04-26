/*
 * timer.h
 *
 *  Created on: May 13, 2018
 *      Author: OS1
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "typedef.h"

class PCB;

extern PCB* mainPCB;

class Timer {
public:
	static void interrupt Int(...);
	static void newInt();
	static void oldInt();
	static void interrupt setVect(int intNo, fnptr isr);
	static fnptr getVect(int intNo);


	static void interrupt (*old)(...);
	static const int IVTE;
};

//void interrupt setVect(int intNo, fnptr isr);
//fnptr getVect(int intNo);
//void interrupt Int(...);
void restore();
void inic();
void interrupt timer(...);

#endif /* TIMER_H_ */
