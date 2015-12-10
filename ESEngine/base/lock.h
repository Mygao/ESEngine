#ifndef BASE_LOCK_H_
#define BASE_LOCK_H_

#include <Windows.h>
#include "thread.h"
#include "macros.h"

namespace base {

class Lock
{
public:
	typedef CRITICAL_SECTION Handle;

	Lock();
	~Lock();

	void Acquire();
	void Release();

	bool Try();

private:
	Handle handle_;

	DISALLOW_COPY_AND_ASSIGN(Lock);
};

class AutoLock
{
public:
	explicit AutoLock(Lock& lock) : lock_(lock)
	{
		lock_.Acquire();
	}

	~AutoLock()
	{
		lock_.Release();
	}

private:
	Lock& lock_;

	DISALLOW_COPY_AND_ASSIGN(AutoLock);
};

} //namespace base

#endif
