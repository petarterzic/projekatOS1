#include "semaphor.h"
#include "krnlSem.h"

Semaphore::Semaphore(int init) {
	myImpl = new KernelSem(init);
}

int Semaphore::wait(int toBlock) {
	return myImpl->wait(toBlock);
}
void Semaphore::signal() {
	myImpl->signal();
}
int Semaphore::val() const {
	return myImpl->val();
}

Semaphore::~Semaphore() {
	delete (myImpl);
}
