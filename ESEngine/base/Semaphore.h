#ifndef BASE_SEMAPHORE_H_
#define BASE_SEMAPHORE_H_

#include <Windows.h>
#include "macros.h"

namespace base {

class Semaphore final
{
public:
	Semaphore(int count);
	~Semaphore();

	void Signal();
	void Wait();

private:
	HANDLE handle_;

	DISALLOW_COPY_AND_ASSIGN(Semaphore);
	
};

} //namespace base

#endif