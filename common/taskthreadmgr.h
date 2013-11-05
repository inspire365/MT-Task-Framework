#ifndef GZ_COMMON_TASK_THREAD_MANAGER_H_
#define GZ_COMMON_TASK_THREAD_MANAGER_H_

#include<list>
#include <inttypes.h>

namespace gz { namespace common { namespace task {

// forward declaration
class TaskQueueIf;
class TaskThread;

/*! \class TaskThreadMgr
    \brief A thread manager for task thread
 *
 *  This manager is also provided with extensibility.
 *  It can be subclassed to override bool Init() and
 *  void Term() to implement specific business logic.
 */
class TaskThreadMgr
{
public:

  /**
   * TaskThreadMgr constructor
   * @param worker_count  The worker threads count
   * @param task_queue    The task queue for worker threads
   */
  TaskThreadMgr(
    uint32_t     worker_count,
    TaskQueueIf& task_queue);

  /**
   * TaskTheadManager destructor
   * virtual for further inheritance
   */
  virtual ~TaskThreadMgr();

  /**
   *  Construct TaskThread
   */
  virtual TaskThread* ConstructTaskThread();

  /*
   * Destroy TaskThread, corresponding to ConstructTaskThread
   */
  virtual void DestroyTaskThread(TaskThread* thr);

  /**
   * Initialization of the manager
   * It can be overrided to implement
   * other specific business logic
   */
  virtual bool Init();

  /**
   * make the worker threads run
   */
  void Start();

  /**
   * Set a stop flag to tell all woker threads stop
   * ***********************  CAUTION ***************************
   * It may be the situation that the workers are waiting for
   * new tasks and know little about the flag. In order to fix
   * this issue, just push some empty jobs to task queue to
   * wake the worker threads
   * ************************************************************
   */
  void Stop();

  /**
   * Terminate the manager, free all resource
   * It can be overrided to implement
   * other specific business logic
   */
  virtual void Term();

protected:

  uint32_t               worker_count_; ///< worker thread count
  TaskQueueIf&           task_queue_;   ///< the task queue for threads
  std::list<TaskThread*> workers_;      ///< task worker threads

}; // TaskThreadMgr

}}} // ::gz::common::task

#endif // GZ_COMMON_TASK_THREAD_MANAGER_IF_H_

