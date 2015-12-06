#include "MessageThread.h"

namespace base {

MessageThread::MessageThread(const std::string& name) : m_strName(name), m_poHandle(0)
{
	m_poMessageLoop = new MessageLoop;
}

MessageThread::~MessageThread()
{
	delete m_poMessageLoop;
}

bool MessageThread::Start()
{
	Thread::Create(this, &m_poHandle);

	return true;
}

void MessageThread::Stop()
{
	std::function<void(void)> task = std::bind(&MessageThread::QuitMessageLoop, this);
	m_poMessageLoop->PostTask(task);
	Thread::Join(m_poHandle);
}

void MessageThread::ThreadMain()
{
	m_poMessageLoop->Run();
}

void MessageThread::QuitMessageLoop()
{
	m_poMessageLoop->Quit();
}

} //namespace base