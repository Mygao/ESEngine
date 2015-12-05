#ifndef BASE_MESSAGELOOP_H_
#define BASE_MESSAGELOOP_H_

#include "TaskQueue.h"
#include "Semaphore.h"

namespace base {

class MessageLoop
{
public:
	MessageLoop();
	~MessageLoop();

	void Run();
	void Quit();

private:
	bool m_bQuit;

	TaskQueue m_oWorkQueue;
	Semaphore* m_poIncomingTaskSemaphore;
};

} //namespace base

#endif