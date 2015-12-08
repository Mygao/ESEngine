#ifndef BASE_MESSAGELOOP_H_
#define BASE_MESSAGELOOP_H_

#include <functional>

#include "task_queue.h"
#include "semaphore.h"

namespace base {

class MessageLoop
{
public:
	MessageLoop();
	~MessageLoop();

	void Run();
	void Quit();

	void PostTask(std::function<void(void)>& task);

private:
	bool quit_;

	TaskQueue work_queue_;
	Semaphore* incoming_task_semaphore_;
};

} //namespace base

#endif