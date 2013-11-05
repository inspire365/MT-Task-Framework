#ifndef GZ_COMMON_TASKQUEUE_IF_H_
#define GZ_COMMON_TASKQUEUE_IF_H_

#include "taskif.h"

namespace gz { namespace common { namespace task {

class TaskQueueIf
{
public:

  virtual ~TaskQueueIf() { /* empty */ }

  /**
   * Try to pop one task from the queue, if the queue is empty,
   * if queue is empty, NULL will be return
   * @return     task pointer
   */
  virtual TaskIf* Pop() = 0;

  /**
   * Push a task to queue
   * @param tk  task pointer
   * @return true to indicate successful, false to fail
   */
  virtual bool Push(TaskIf* tk) = 0;

  /**
   * Get the total size of the queue
   */
  virtual size_t size() = 0;

  /**
   * check if the queue empty
   */
  virtual bool empty() = 0;

protected:

  TaskQueueIf() { /* empty */ }

};

}}} // ::gz::common::task

#endif // GZ_COMMON_TASKQUEUE_IF_H_

