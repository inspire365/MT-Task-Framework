/**
 * @file simplelock.h
 */
#ifndef GZ_COMMON_CONCURRENCY_SIMPLELOCK_H_
#define GZ_COMMON_CONCURRENCY_SIMPLELOCK_H_

#include <pthread.h>

namespace gz { namespace common { namespace concurrency {

/**
 * @class SimpleLock
 *
 * A simple wrapper of pthread_mutex_t. It can be worked with ::gz::utility::AutoDone
 */
class SimpleLock
{
public:
  SimpleLock();
  ~SimpleLock();
  
  /**
   * Lock the code critical section
   */
  void Lock();

  /**
   * Leave the code critical section
   */
  void Unlock();

private:

  pthread_mutex_t mutex_;

}; // SimpleLock

}}} // ::gz::common::concurrency

#endif// GZ_COMMON_CONCURRENCY_SIMPLELOCK_H_

