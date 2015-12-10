#ifndef BASE_THREAD_H_
#define BASE_THREAD_H_

#include "macros.h"

namespace base {

class ThreadHandle
{
public:
	typedef void* Handle;

	ThreadHandle() : handle_(0) {}

	explicit ThreadHandle(Handle handle) : handle_(handle) {}

	Handle GetHandle() { return handle_; }

private:
	Handle handle_;
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

	static bool Create(Delegate* delegate, ThreadHandle* out_handle);
	static void Join(ThreadHandle handle);

	DISALLOW_IMPLICIT_CONSTRUCTORS(Thread);
};

} //namespace base

#endif //BASE_THREAD_H_
