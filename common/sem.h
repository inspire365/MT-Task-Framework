/**
    sem.cpp
    Purpose: Semaphore wrapper for Task queue

    @author Dan, 365days.enjoy%gmail.com
*/

#ifndef GZ_COMMON_SEMAPHORE_H_
#define GZ_COMMON_SEMAPHORE_H_
// std or system
#include <semaphore.h>
#include <inttypes.h>

namespace gz { namespace common { namespace concurrency {

/*! \class Semaphore
    \brief A simple wrapper class of unnamed semaphore
 */
class Semaphore
{
public:

  /**
   * Constructor of Semaphore
   * @param value  The vaue argument specifies the initial value
   *               for the semaphore
   */
  Semaphore(uint32_t value = 0);
  ~Semaphore();

  /**
   * Increments  (unlocks) the semaphore
   * @return     errno
   */
  int Post();

  /**
   * Decrements  (locks)  the semaphore. If the semaphore's
   * value is greater than zero, then the decrement proceeds,
   * and the function returns, immediately.  If the semaphore
   * currently has the value zero, then the call blocks  until
   * either it becomes possible to perform the decrement
   * (i.e., the semaphore value rises above zero), or a signal handler
   * interrupts the call
   * @return    errno
   */
  int Wait();

  /**
   * The same as Wait, except that the time specifies a limit
   * on the amount of time that the call should block if the
   * decrement cannot be immediately performed.
   * @param timeout    the timeout of the wait
   * @return           errno
   */
  int TimedWait(const struct timespec& timeout);

private:

  //uint32_t value_;  ///< the initial value for the semaphore
  sem_t    sem_;    ///< the unnamed semaphore

};

}}} // ::gz::common::concurrency

#endif // GZ_COMMON_SEMAPHORE_H_

