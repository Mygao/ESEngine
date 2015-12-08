#include "thread.h"

#include <Windows.h>

namespace base {

namespace {

struct ThreadParams
{
	Thread::Delegate* delegate;
};

DWORD __stdcall ThreadFunc(void* in_params)
{
	ThreadParams* params = static_cast<ThreadParams*>(in_params);
	Thread::Delegate* pLocalDelegate = params->delegate;

	delete params;

	pLocalDelegate->ThreadMain();

	return 0;
}

}

bool Thread::Create(Delegate* delegate, ThreadHandle* out_handle)
{
	if (out_handle == nullptr)
	{
		return false;
	}

	ThreadParams* params = new ThreadParams;

	params->delegate = delegate;

	ThreadHandle::Handle handle = 
		CreateThread(nullptr, 0, ThreadFunc, params, 0, nullptr);

	if (!handle)
	{
		delete params;
		return false;
	}

	*out_handle = ThreadHandle(handle);

	return true;
}

void Thread::Join(ThreadHandle handle)
{
	WaitForSingleObject(handle.GetHandle(), INFINITE);

	CloseHandle(handle.GetHandle());
}

} //namespace base