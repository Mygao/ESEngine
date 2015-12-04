#include "MessageThread.h"

namespace base {

MessageThread::MessageThread(const std::string& name) : m_strName(name), m_poHandle(0)
{

}

MessageThread::~MessageThread()
{

}

bool MessageThread::Start()
{
	Thread::Create(this, &m_poHandle);

	return true;
}

void MessageThread::Stop()
{
	Thread::Join(m_poHandle);
}

void MessageThread::ThreadMain()
{
	m_poMessageLoop->Run();
}

} //namespace base