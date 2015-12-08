#ifndef BASE_MESSAGETHREAD_H_
#define BASE_MESSAGETHREAD_H_

#include <string>

#include "thread.h"
#include "message_loop.h"

namespace base {

class MessageThread : Thread::Delegate
{
public:
	explicit MessageThread(const std::string& name);
	~MessageThread() override;

	bool Start();
	void Stop();

	ThreadHandle GetHandle() { return handle_; }

private:
	virtual void ThreadMain() override;
	void QuitMessageLoop();

	ThreadHandle handle_;
	MessageLoop* message_loop_;

	std::string name_;

	DISALLOW_COPY_AND_ASSIGN(MessageThread);
};

} //namespace base

#endif