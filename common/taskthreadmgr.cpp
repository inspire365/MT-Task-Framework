#include "taskthreadmgr.h"
// app common
#include "taskqueueif.h"
#include "taskthread.h"

namespace gz { namespace common { namespace task {

TaskThreadMgr::TaskThreadMgr(
      uint32_t     worker_count,
      TaskQueueIf& task_queue):
      worker_count_(worker_count),
      task_queue_(task_queue)
{
  if(worker_count_ < 1)
  {
    worker_count_ = 1;
  }
}

TaskThreadMgr::~TaskThreadMgr()
{
  this->Stop();
}

TaskThread* TaskThreadMgr::ConstructTaskThread()
{
  TaskThread* thr = new TaskThread(task_queue_);
  return thr;
}

void TaskThreadMgr::DestroyTaskThread(TaskThread* thr)
{
  if (thr)
  {
    delete thr;
  }
}

bool TaskThreadMgr::Init()
{
  TaskThread* thr = NULL;
  for (uint32_t i = 0; i < worker_count_; ++i)
  {
    thr = this->ConstructTaskThread();
    if (thr->Init())
    {
      workers_.push_back(thr);
    }
    else
    {
      // ::syslog(LOG_ERR, "!!!!!!! Fail to Init the %uth thread !!!!!!", i);
    }
  }
  //For inheritance, other initialization code goes here

  return true;
}

void TaskThreadMgr::Start()
{
  std::list<TaskThread*>::const_iterator lit = workers_.begin();
  std::list<TaskThread*>::const_iterator eit = workers_.end();
  for (; lit != eit; ++lit)
  {
    (*lit)->Start();
  }
}

void TaskThreadMgr::Stop()
{
  std::list<TaskThread*>::const_iterator lit = workers_.begin();
  std::list<TaskThread*>::const_iterator eit = workers_.end();
  for (; lit != eit; ++lit)
  {
    (*lit)->Stop(true);
  }
}

void TaskThreadMgr::Term()
{
  std::list<TaskThread*>::iterator it = workers_.begin();
  for(; it != workers_.end(); ++it)
  {
    (*it)->Term();
    this->DestroyTaskThread(*it);
    *it = NULL;
  }
  workers_.clear();
  //For inheritance, other code goes here

}

}}} // ::gz::common::task

