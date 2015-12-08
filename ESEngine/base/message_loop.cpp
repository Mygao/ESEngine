#include "message_loop.h"

#include <iostream>

namespace base {

MessageLoop::MessageLoop() : quit_(false)
{
	incoming_task_semaphore_ = new Semaphore(0);
}

MessageLoop::~MessageLoop()
{
	delete incoming_task_semaphore_;
}

void MessageLoop::Run()
{
	std::cout << "MessageLoop::Run() - Thread Started" << std::endl;
	for (;;)
	{
		//Dequeing and doing task loop
		if (work_queue_.empty())
		{
			//Reload Queue
		}

		if (!work_queue_.empty())
		{
			std::function<void(void)> task = work_queue_.front();
			task();
		}


		if (quit_)
		{
			break;
		}

		//Wait
		incoming_task_semaphore_->Wait();
	}

	std::cout << "MessageLoop::Run() - Thread Ended" << std::endl;
}

void MessageLoop::Quit()
{
	quit_ = true;
}

void MessageLoop::PostTask(std::function<void(void)>& task)
{
	work_queue_.push(task);
	incoming_task_semaphore_->Signal();
}

} //namespace base