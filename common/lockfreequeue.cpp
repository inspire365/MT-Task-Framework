#include "taskif.h"
#include "lockfreequeue.h"

namespace gz { namespace common { namespace task {

LockFreeQueue::LockFreeQueue(
    uint32_t queue_threshold,
    uint32_t queue_max_limit):
    queue_threshold_(queue_threshold),
    queue_max_limit_(queue_max_limit),
    queue_size_(0),
    queue_(queue_max_limit)
{
  if (queue_max_limit_ > 100)
  {
    // should little below the the real limit
    // In order to make it thread-safe, for the
    // reason of boost lock free queue:
    // If internal memory pool is exhausted
    // and the memory pool is not fixed-sized,
    // a new node will be allocated from the OS.
    // This may not be lock-free.
    queue_max_limit -= 100;
  }
}

LockFreeQueue::~LockFreeQueue()
{
  TaskIf* task = NULL;
  while(queue_.pop(task))
  {
    --queue_size_;
    if(task)
    {
      task->Release();
      task = NULL;
    }
  }  // end while
}

TaskIf* LockFreeQueue::Pop()
{
  semaphore_.Wait();
  TaskIf* task = NULL;
  if (queue_.pop(task))
  {
     --queue_size_;
  }
  return task;
}

bool LockFreeQueue::Push(TaskIf* tk)
{
  if(queue_.push(tk))
  {
    ++queue_size_;
  }
  if (queue_size_ > queue_max_limit_)
  {
    TaskIf* task = NULL;
    if (queue_.pop(task))
    {   // drop one task for more space
      --queue_size_;
      if (task)
      {
        task->Release();
      }
    } // pop
    //   send alarm ???
  }
  else
  {
    if ( queue_size_ > queue_threshold_ )
    {
      // task queue size above threshold
      // send alarm ???
    }
    semaphore_.Post();
  }
  return true;
}

size_t LockFreeQueue::size()
{
  return queue_size_;
}

bool LockFreeQueue::empty()
{
  return queue_size_;
}

}}} // ::gz::common::task

