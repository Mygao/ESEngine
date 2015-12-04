#include "MessageLoop.h"

namespace base {

MessageLoop::MessageLoop() : m_bQuit(false)
{

}

MessageLoop::~MessageLoop()
{

}

void MessageLoop::Run()
{
	for (;;)
	{
		//Dequeing and doing task loop

		if (m_bQuit)
		{
			break;
		}
	}
}

void MessageLoop::Quit()
{
	m_bQuit = true;
}

} //namespace base