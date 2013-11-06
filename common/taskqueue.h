/**
    taskqueue.h
    Purpose: A default first-in-first-out task queue to hold tasks

    @author Dan, 365days.enjoy%gmail.com
*/

#ifndef GZ_COMMON_TASK_QUEUE_H_
#define GZ_COMMON_TASK_QUEUE_H_
#include <queue>
#include "sem.h"
#include "simplelock.h"
#include "taskqueueif.h"

namespace gz { namespace common { namespace task {

using ::gz::common::concurrency::SimpleLock;
using ::gz::common::concurrency::Semaphore;

/// forward declaration
class TaskIf;

/*! \class TaskQueue
    \brief A thread safe Task Queue for multiple thread environment
 */
class TaskQueue : public TaskQueueIf
{
public:

  TaskQueue(
    uint32_t queue_threshold = 30000,
    uint32_t queue_max_limit = 35000);

  virtual ~TaskQueue();

  /**
   * Try to pop one task from the queue, if the queue is empty,
   * if queue is empty, NULL will be return
   * @return     task pointer
   */
  virtual TaskIf* Pop();

  /**
   * Push a task to queue
   * @param tk  task pointer
   * @return true to indicate successful, false to fail
   */
  virtual bool Push(TaskIf* tk);

  /**
   * Get the total size of the queue
   */
  virtual size_t size();

  /**
   * check if the queue empty
   */
  virtual bool empty();

private:

  Semaphore           semaphore_;
  SimpleLock          lock_;
  std::queue<TaskIf*> tasks_;
  uint32_t            queue_threshold_;
  uint32_t            queue_max_limit_;

}; // TaskQueue

}}} // ::gz::common::task

#endif // GZ_COMMON_TASK_QUEUE_H_

