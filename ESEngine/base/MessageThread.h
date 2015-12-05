#ifndef BASE_MESSAGETHREAD_H_
#define BASE_MESSAGETHREAD_H_

#include <string>

#include "Thread.h"
#include "MessageLoop.h"

namespace base {

class MessageThread : Thread::Delegate
{
public:
	explicit MessageThread(const std::string& name);
	~MessageThread() override;

	bool Start();
	void Stop();

	ThreadHandle GetHandle() { return m_poHandle; }

private:
	virtual void ThreadMain() override;

	ThreadHandle m_poHandle;
	MessageLoop* m_poMessageLoop;

	std::string m_strName;

	DISALLOW_COPY_AND_ASSIGN(MessageThread);
};

} //namespace base

#endif