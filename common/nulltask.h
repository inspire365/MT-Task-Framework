#ifndef NULL_TASK_H_
#define NULL_TASK_H_

#include "taskif.h"

namespace gz { namespace common { namespace task {

/*! \class NullTask
    \An Null Task to push to taskqueue to wake the thread to exit
 */
class NullTask : public TaskIf
{
public:

  NullTask() { /* empty */ }

  virtual ~NullTask() { /* empty */ }

  virtual void Execute(
    void* thread_context,
    void* app_context)
  {
    // ::syslog(LOG_INFO, "NUll Task to make the thread exit");
  }

  virtual void Release()
  {
    delete this;
  }

}; // NullTask;

}}} // ::gz::common::task;

#endif // NULL_TASK_H_

