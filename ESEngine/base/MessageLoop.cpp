#include "MessageLoop.h"

#include <iostream>

namespace base {

MessageLoop::MessageLoop() : m_bQuit(false)
{
	m_poIncomingTaskSemaphore = new Semaphore(0);
}

MessageLoop::~MessageLoop()
{
	delete m_poIncomingTaskSemaphore;
}

void MessageLoop::Run()
{
	std::cout << "MessageLoop::Run() - Thread Started" << std::endl;
	for (;;)
	{
		//Dequeing and doing task loop
		if (m_oWorkQueue.empty())
		{
			//Reload Queue
		}
		
		if (m_bQuit)
		{
			break;
		}

		//Wait
		m_poIncomingTaskSemaphore->Wait();
	}

	std::cout << "MessageLoop::Run() - Thread Ended" << std::endl;
}

void MessageLoop::Quit()
{
	m_bQuit = true;
}

void MessageLoop::PostTask(std::function<void(void)>& task)
{
	m_poIncomingTaskSemaphore->Signal();
}

} //namespace base