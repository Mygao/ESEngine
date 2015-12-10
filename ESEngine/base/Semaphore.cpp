#include "semaphore.h"

namespace base {

Semaphore::Semaphore(int count)
{
	handle_ = CreateSemaphoreA(NULL, count, 0x7fffffff, NULL);
}

Semaphore::~Semaphore()
{
	CloseHandle(handle_);
}

void Semaphore::Signal()
{
	LONG temp;
	ReleaseSemaphore(handle_, 1, &temp);
}

void Semaphore::Wait()
{
	WaitForSingleObject(handle_, INFINITE);
}

} //namespace base