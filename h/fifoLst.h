/*
 * pcblst.h
 *
 *  Created on: May 12, 2018
 *      Author: OS1
 */

#ifndef FIFOLST_H_
#define FIFOLST_H_

class PCB;

struct Element {
	PCB* pcb;
	Element* next;
	Element() {
		pcb = 0;
		next = 0;
	}
	Element(PCB* pcb) {
		this->pcb = pcb;
		next = 0;
	}
};

class PCBList {

private:
	struct Element* head;
	struct Element* last;
public:
	PCBList();
	void PutInList(PCB* newPCB);
	void remove(PCB* pcb);
	PCB* removeFirst();
	int isEmpty();

};

#endif /* FIFOLST_H_ */
