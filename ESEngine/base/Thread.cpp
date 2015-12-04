#include "Thread.h"

#include <Windows.h>

namespace base {

namespace {

struct ThreadParams
{
	Thread::Delegate* m_poDelegate;
};

DWORD __stdcall ThreadFunc(void* pParams)
{
	ThreadParams* pLocalParams = static_cast<ThreadParams*>(pParams);
	Thread::Delegate* pLocalDelegate = pLocalParams->m_poDelegate;

	delete pLocalParams;

	pLocalDelegate->ThreadMain();

	return 0;
}

}

bool Thread::Create(Delegate* poDelegate, ThreadHandle* pOutThreadHandle)
{
	if (pOutThreadHandle == nullptr)
	{
		return false;
	}

	ThreadParams* poParams = new ThreadParams;

	poParams->m_poDelegate = poDelegate;

	ThreadHandle::Handle pThreadHandle = CreateThread(nullptr, 0, ThreadFunc, poParams, 0, nullptr);

	if (!pThreadHandle)
	{
		delete poParams;
		return false;
	}

	*pOutThreadHandle = ThreadHandle(pThreadHandle);

	return true;
}

void Thread::Join(ThreadHandle poHandle)
{
	WaitForSingleObject(poHandle.GetHandle(), INFINITE);

	CloseHandle(poHandle.GetHandle());
}

} //namespace base