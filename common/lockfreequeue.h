#ifndef GZ_COMMON_LOCK_FREE_QUEUE_H_
#define GZ_COMMON_LOCK_FREE_QUEUE_H_

#include "sem.h"
#include "taskqueueif.h"
#include <boost/atomic.hpp>
#include <boost/lockfree/queue.hpp>

namespace gz { namespace common { namespace task {

using ::gz::common::concurrency::Semaphore;

/// forward declaration
class TaskIf;

class LockFreeQueue : public TaskQueueIf
{
public:

  LockFreeQueue(
    uint32_t queue_threshold = (1<<10),
    uint32_t queue_max_limit = (1<<11));

  virtual ~LockFreeQueue();

  virtual TaskIf* Pop();

  virtual bool Push(TaskIf* tk);

  virtual size_t size();

  virtual bool empty();

private:

  Semaphore           semaphore_;
  uint32_t            queue_threshold_;
  uint32_t            queue_max_limit_;

  boost::atomic_uint32_t          queue_size_;
  boost::lockfree::queue<TaskIf*> queue_;

};   // LockFreeQueue

}}} // ::gz::common::task

#endif // GZ_COMMON_LOCK_FREE_QUEUE_H_

