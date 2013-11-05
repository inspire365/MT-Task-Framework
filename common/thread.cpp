#include "thread.h"
#include <assert.h>

namespace gz { namespace common { namespace thread {

Thread::Thread():
  alive_(false),
  stop_(false),
  thread_id_(0),
  thread_attr_(NULL)
{
  // empty
}

Thread::~Thread()
{
  // empty
}

int Thread::Start()
{
  // if create successful, will return 0
  int err = pthread_create(&thread_id_, thread_attr_,
    ThreadProc, (void*)(this));
  // ::syslog(LOG_INFO, "Thread::Start(), code: %d", err);
  return err;
}

void* Thread::ThreadProc(void* arg)
{
  assert(arg);
  Thread* self = (Thread*)(arg);
  // keep thread id for latter use to make it more safe
  int threadid = (int)(self->thread_id_);
  self->alive_ = true;
  try
  {
    self->Run();
  }
  catch(...)
  {
    // ::syslog(LOG_ERR, "Thread::ThreadProc catch exception, thread id: %d", threadid);
  }
  self->alive_ = false;
  if (self->release_)
  {
    delete self;
  }
  return (void*)(0);
}

void Thread::Join()
{
  pthread_join(thread_id_, NULL);
  thread_id_ = 0;
  alive_ = false;
}

}}}  // end namespace gz::common::thread

