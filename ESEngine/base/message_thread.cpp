#include "message_thread.h"

namespace base {

MessageThread::MessageThread(const std::string& name) : name_(name), handle_(0)
{
	message_loop_ = new MessageLoop;
}

MessageThread::~MessageThread()
{
	delete message_loop_;
}

bool MessageThread::Start()
{
	Thread::Create(this, &handle_);

	return true;
}

void MessageThread::Stop()
{
	std::function<void(void)> task = std::bind(&MessageThread::QuitMessageLoop, this);
	message_loop_->PostTask(task);
	Thread::Join(handle_);
}

void MessageThread::ThreadMain()
{
	message_loop_->Run();
}

void MessageThread::QuitMessageLoop()
{
	message_loop_->Quit();
}

} //namespace base