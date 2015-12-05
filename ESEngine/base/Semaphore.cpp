#include "Semaphore.h"

namespace base {

Semaphore::Semaphore(int count)
{
	m_poHandle = CreateSemaphoreA(NULL, count, 0x7fffffff, NULL);
}

Semaphore::~Semaphore()
{
	CloseHandle(m_poHandle);
}

void Semaphore::Signal()
{
	LONG temp;
	ReleaseSemaphore(m_poHandle, 1, &temp);
}

void Semaphore::Wait()
{
	WaitForSingleObject(m_poHandle, INFINITE);
}

}