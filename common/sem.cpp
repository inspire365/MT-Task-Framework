/**
    sem.cpp
    Purpose: Semaphore wrapper for Task queue

    @author Dan, 365days.enjoy%gmail.com
*/

#include "sem.h"
// std or system
#include <stdexcept>
#include <errno.h>
#include <stdio.h>

namespace gz { namespace common { namespace concurrency {

static const uint32_t kBufLen = 128;

Semaphore::Semaphore(uint32_t value)
{
  int sys_errno = 0;
  int err = ::sem_init( &sem_, 0, value );
  if ( 0 != err )
  {
    sys_errno = errno; // if -1 is returned, and errno is set to indicate the error
    char buf[kBufLen] = {0};
    snprintf(buf, kBufLen, "Error #%d on ::sem_init, errno:: %d", err, sys_errno);
    //::syslog( LOG_ERR, "%s", buf);
    throw std::runtime_error(buf);
  }
}

Semaphore::~Semaphore()
{
  int sys_errno = 0;
  int err = ::sem_destroy( &sem_ );
  if ( 0 != err )
  {
    sys_errno = errno; // if -1 is returned, and errno is set to indicate the error.
    //::syslog( LOG_ERR, "Error #%d on ::sem_destroy, errno: %d", err, sys_errno);
  }
}

int Semaphore::Post()
{
  int sys_errno = 0;
  int err = sem_post( &sem_ );
  if ( err )
  {
    sys_errno = errno; // if -1 is returned, and errno is set to indicate the error.
    //::syslog( LOG_ERR, "Error #%d on ::sem_post, errno: %d", err, sys_errno);
  }
  return sys_errno;
}

int Semaphore::Wait()
{
  int sys_errno = 0;
  int err = ::sem_wait( &sem_ );
  if ( 0 != err )
  {
    sys_errno = errno; // if -1 is returned, and errno is set to indicate the error.
    // ::syslog( LOG_ERR, "Error #%d on ::sem_wait, errno: %d", err, sys_errno);
  }
  return sys_errno;
}

int Semaphore::TimedWait(const struct timespec& timeout)
{
  int sys_errno = 0;
  int err = ::sem_timedwait( &sem_, &timeout);
  if ( 0 != err )
  {
    sys_errno = errno; // if -1 is returned, and errno is set to indicate the error.
    // ::syslog( LOG_ERR, "Error #%d on ::sem_timedwait, errno: %d", err, sys_errno);
  }
  return sys_errno;
}

}}} // ::gz::common::concurrency

