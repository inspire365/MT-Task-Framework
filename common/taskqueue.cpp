/**
    taskqueue.cpp
    Purpose: A default first-in-first-out task queue to hold tasks

    @author Dan, 365days.enjoy%gmail.com
*/

#include "taskif.h"
#include "autodone.h"
#include "taskqueue.h"
#include <cassert>
#include <errno.h>
#include <stdexcept>

namespace gz { namespace common { namespace task {

using ::gz::common::utility::AutoDone;

TaskQueue::TaskQueue(
    uint32_t queue_threshold,
    uint32_t queue_max_limit):
    queue_threshold_(queue_threshold),
    queue_max_limit_(queue_max_limit)
{
  // empty
}

TaskQueue::~TaskQueue()
{
  TaskIf* tk = NULL;
  AutoDone< SimpleLock > guard( lock_, &SimpleLock::Lock, &SimpleLock::Unlock );
  while ( !tasks_.empty() )
  {
    tk = tasks_.front();
    tasks_.pop();
    tk->Release(); // release resource
  }
}

TaskIf* TaskQueue::Pop()
{
  semaphore_.Wait();
  TaskIf* tk = NULL;
  AutoDone< SimpleLock > guard( lock_, &SimpleLock::Lock, &SimpleLock::Unlock );
  if ( !tasks_.empty() )
  {
    tk = tasks_.front();
    tasks_.pop();
  }
  return tk;
}

bool TaskQueue::Push(TaskIf* tk)
{
  assert(tk);
  bool ret = true;
  try
  {
    AutoDone< SimpleLock > guard( lock_, &SimpleLock::Lock, &SimpleLock::Unlock );
    tasks_.push( tk );
    size_t queue_size = tasks_.size();
    if ( queue_size > queue_max_limit_)
    {
      //task queue reach max limit, drop one oldest task
      tk = tasks_.front();
      tasks_.pop();    // drop the old task
      tk->Release();
    }
    else
    {
      if ( queue_size > queue_threshold_ )
      {
        // task queue size above threshold
      }
      semaphore_.Post();
    }
  }
  catch ( std::exception& e)
  {
    // Failed to queue task: %s", e.what()
    ret = false;
  }
  catch(...)
  {
    // unknown exception"
    ret = false;
  }
  return ret;
}

size_t TaskQueue::size()
{
  // maybe in this situation, we can remove the lock?
  AutoDone< SimpleLock > guard( lock_, &SimpleLock::Lock, &SimpleLock::Unlock );
  return tasks_.size();
}

bool TaskQueue::empty()
{
  // maybe in this situation, we can remove the lock?
  AutoDone< SimpleLock > guard( lock_, &SimpleLock::Lock, &SimpleLock::Unlock );
  return tasks_.empty();
}

}}} // ::gz::common::task

