/**
    taskthread.cpp
    Purpose: A default task thread to process the taskqueue tasks

    @author Dan, 365days.enjoy%gmail.com
*/

#include "taskthread.h"
// std
#include <stdexcept>
// app common
#include "taskif.h"
#include "taskqueueif.h"

namespace gz { namespace common { namespace task {

TaskThread::TaskThread(TaskQueueIf& tq):
  task_queue_(tq)
{
  // empty
}

TaskThread::~TaskThread()
{
  // empty
}

void TaskThread::Run()
{
  while(!this->Stop())
  {
    if(!this->Action())
    {
      break;
    }
  }
}

bool TaskThread::Action()
{
  TaskIf* tk = task_queue_.Pop();
  if (tk)
  {
    try
    {           // Do you want to pass some argument from the thread to
      tk->Execute(this, NULL); // the command ? if yes, override it
      tk->Release();     // release resource
      tk = NULL;
    }
    catch(const std::exception& e)
    {
      //::syslog( LOG_ERR, "Catch Exception: %s", e.what() );
    }
    catch(...)
    {
      //::syslog(LOG_ERR, "Catch unknown exception");
    }
  }
  return true;  // if false, indicate to tell the thread to exit
}

void TaskThread::Term()
{
  pthread_join(thread_id_, NULL);
  thread_id_ = 0;
  alive_ = false;
}

}}} // ::gz::common::task

