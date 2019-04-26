/*
 * fifolst.cpp
 *
 *  Created on: May 12, 2018
 *      Author: OS1
 */

#include "fifolst.h"

PCBList::PCBList() {
	head = 0;
	last = 0;
}

void PCBList::PutInList(PCB* newPCB) {
	Element* newElement = new Element(newPCB);

	if (head == 0) {
		head = newElement;
		last = head;
	}

	else {
		last->next = newElement;
		last = newElement;
	}
	last->next = 0;
}

void PCBList::remove(PCB* pcb) {
	if (head == 0)
		return;
	if (head->pcb == pcb) {
		Element* del = head;
		head = head->next;
		del->pcb = 0;
		delete (del);
		return;
	}
	Element* iterator = head;
	Element* prev = 0;
	while (iterator != 0) {

		if (iterator->pcb == pcb) {
			prev->next = iterator->next;
			iterator->pcb = 0;
			iterator->next = 0;
			delete (iterator);
			return;
		}

		prev = iterator;
		iterator = iterator->next;
	}
}

PCB* PCBList::removeFirst() {
	if (head == 0)
		return 0;
	Element* retel = head;
	head = head->next;
	retel->next = 0;
	PCB* ret = retel->pcb;
	retel->pcb = 0;
	delete retel;
	return ret;
}

int PCBList::isEmpty() {
	if (!head)
		return 1;
	return 0;
}
