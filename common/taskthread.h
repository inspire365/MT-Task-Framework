#ifndef GZ_COMMON_TASK_THREAD_H_
#define GZ_COMMON_TASK_THREAD_H_

#include "thread.h"

namespace gz { namespace common { namespace task {

using ::gz::common::thread::Thread;

// forward declaration
class TaskQueueIf;

/*! \class TaskThread
    \brief A thread implementation for task queue
 *
 *  Derived from Thread class, TaskThread implements as a
 *  worker thread for TaskQueue. It gets task from the queue
 *  one by one and execute the task. TaskThread can be extended
 *  by subclassing to override the virtual bool Action() to
 *  implement specific business logic
 */
class TaskThread : public Thread
{
  public:

    TaskThread(TaskQueueIf& tq);
    virtual ~TaskThread();

    /**
     * Derived from Thread class
     */
    virtual void Run();

    /**
     * This method can be overrided to implement other
     * specific logic
     */
    virtual bool Action();

  /**
   * Terminate the thread
   */
  void Term();

  protected:

    TaskQueueIf& task_queue_;  ///< the task queue for the task thread

};

}}} // ::gz::common::task

#endif // GZ_COMMON_TASK_THREAD_H_

