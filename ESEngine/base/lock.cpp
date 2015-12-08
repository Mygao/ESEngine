#include "lock.h"

namespace base {

Lock::Lock()
{
	::InitializeCriticalSectionAndSpinCount(&handle_, 2000);
}

Lock::~Lock() 
{
	::DeleteCriticalSection(&handle_); 
}

void Lock::Acquire()
{
	::EnterCriticalSection(&handle_);
}

void Lock::Release()
{ 
	::LeaveCriticalSection(&handle_); 
}

bool Lock::Try()
{
	if (::TryEnterCriticalSection(&handle_) != FALSE)
	{
		return true;
	}

	return false;
}

}