/*
 * timeLst.cpp
 *
 *  Created on: May 13, 2018
 *      Author: OS1
 */

#include "timeLst.h"
#include "SCHEDULE.H"
#include "pcb.h"
#include <IOSTREAM.H>

TimeListElem::TimeListElem(PCB* pcb, Time time_to_sleep) {
	timeToSleep = time_to_sleep;
	this->pcb = pcb;
	next = 0;
}

TimeList::TimeList() {
	head = 0;
}

TimeList::~TimeList() {
	TimeListElem* del = head;
	while (del) {
		head = del;
		del = del->next;
		head->pcb = 0;
		delete (head);
	}
}

void TimeList::PutInList(PCB* pcb, Time timeToSleep) {
	TimeListElem* newElem = new TimeListElem(pcb, timeToSleep);

	if (head == 0)
		head = newElem;

	else {
		if (timeToSleep <= head->timeToSleep) {
			newElem->next = head;
			head->timeToSleep -= newElem->timeToSleep;
			head = newElem;
			return;
		}

		TimeListElem* iterator = head;
		TimeListElem* prev = 0;

		while (iterator->next && newElem->timeToSleep >= iterator->timeToSleep) {
			newElem->timeToSleep -= iterator->timeToSleep;
			prev = iterator;
			iterator = iterator->next;
		}
		if (iterator->next == 0
				&& newElem->timeToSleep >= iterator->timeToSleep) {
			iterator->next = newElem;
			newElem->timeToSleep -= iterator->timeToSleep;
		} else {
			prev->next = newElem;
			newElem->next = iterator;
			iterator->timeToSleep -= newElem->timeToSleep;
		}
	}
}

void TimeList::remove(PCB* pcb) {
	if (head == 0)
		return;
	if (head->pcb == pcb) {
		TimeListElem* newElem = head;
		head = head->next;
		head->timeToSleep += newElem->timeToSleep;
		newElem->pcb = 0;
		delete (newElem);
		return;
	}
	TimeListElem* iterator = head;
	TimeListElem* prev = 0;
	while (iterator && iterator->pcb != pcb) {
		prev = iterator;
		iterator = iterator->next;
	}
	if (iterator == 0)
		return;
	prev->next = iterator->next;
	if (iterator->next)
		iterator->next->timeToSleep += iterator->timeToSleep;
	iterator->pcb = 0;
	delete (iterator);
}

void TimeList::update() {
//	lock
//	cout<<"update"<<endl;
//	unlock
	if (head == 0)
		return;
	head->timeToSleep--;
	while (head && head->timeToSleep == 0) {
		TimeListElem* ret = head;
		head = head->next;
		ret->pcb->state = PCB::ready;
		Scheduler::put(ret->pcb);
		ret->pcb = 0;
		delete (ret);
	}
}

//void TimeList::ispis() {
//
//	TimeListElem* iterator = head;
//	while (iterator) {
//		lock
//		cout << iterator->timeToSleep << " ";
//		unlock
//		iterator = iterator->next;
//	}lock
//	cout << endl;
//unlock
//}

