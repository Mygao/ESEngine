#ifndef BASE_THREAD_H_
#define BASE_THREAD_H_

#include "macros.h"

namespace base {

class ThreadHandle
{
public:
	typedef void* Handle;

	ThreadHandle() : m_poHandle(0) {}

	explicit ThreadHandle(Handle handle) : m_poHandle(handle) {}

	Handle GetHandle() { return m_poHandle; }

private:
	Handle m_poHandle;
};

class Thread
{
public:
	class Delegate
	{
	public:
		virtual void ThreadMain() = 0;

	protected:
		virtual ~Delegate() {}

	};

	static bool Create(Delegate* poDelegate, ThreadHandle* pOutThreadHandle);
	static void Join(ThreadHandle poThreadHandle);

	DISALLOW_IMPLICIT_CONSTRUCTORS(Thread);
};

}

#endif //BASE_THREAD_H_
