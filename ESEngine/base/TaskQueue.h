#ifndef BASE_TASKQUEUE_H_
#define BASE_TASKQUEUE_H_

#include <queue>
#include <functional>

namespace base {

class TaskQueue : std::queue<std::function<void(void)>>
{
public:
	void Swap(TaskQueue* queue) { c.swap(queue->c); }
};

} //namespace base
#endif