/**
    threadif.h
    Purpose: A thread wrapper class

    @author Dan, 365days.enjoy%gmail.com
*/

#ifndef GZ_COMMON_THREADIF_H_
#define GZ_COMMON_THREADIF_H_
// std or system
#include <pthread.h>

namespace gz { namespace common { namespace thread {

/*! \class ThreadIf
    \brief A base thread wrapper
 *
 *  A simple base wrapper class for pthread
 *  This base class provides flexibility for
 *  users to override the Run interface to
 *  implement their own logic.
 */
class ThreadIf
{
public:

  /**
   * ThreadIf constructor
   */
  ThreadIf();

  /**
   * ThreadIf destructor
   * virtual for further inheritance
   */
  virtual ~ThreadIf();

  virtual bool Init() { /* default empty */ return true; }

  virtual void Term()
  {
    // Base on different thread setting,
    // choose different way to terminate
    // for example:
    //pthread_join(thread_id_, NULL);
    //thread_id_ = 0;
    //alive_ = false;
  }

  /**
   * Get this thread's thread id
   * @return  thread id
   */
  inline pthread_t thread_id() const
  {
    return thread_id_;
  }

  /**
   * Make thread Run
   * @return If successful, return zero; otherwise, an error
   *         number shall be returned to indicate the error
   */
  int Start();

  /**
   * Make a flag to tell the thread stop running or not
   */
  inline void Stop(bool flag)
  {
    stop_ = flag;
  }

  /**
   * Check if the thread should stop running
   */
  inline bool Stop() const
  {
    return stop_;
  }

  /*
   *  Make a flag to tell the thread release or not
   */
  inline void Release(bool flag)
  {
    release_ = flag;
  }

  /*
   *  thr thread detach self
   */
  inline void Detach()
  {
    pthread_detach(thread_id_);
  }

  /**
   * Wait the thread to exit
   */
  void Join();

  /**
   * To check if the thread is still live
   * @return true for live, false for dead
   */
  inline bool alive() const
  {
    return alive_;
  }

protected:

  /**
   * Override this virtual function to implement your own logic
   */
  virtual void Run() = 0;

private:

  /// disable some constructors and assignment operators
  ThreadIf(const ThreadIf& thr);
  ThreadIf& operator = (const ThreadIf& thr);

  /// thread start routine
  static void* ThreadProc(void* arg);

protected:

  bool            alive_;        ///< if the thread is still alive?
  bool            stop_;         ///< tell the thread to stop, reserved for future extension
  pthread_t       thread_id_;    ///< thread id
  pthread_attr_t* thread_attr_;  ///< set the thread's attribute, for future extension
  bool            release_;      ///< tell the thread to release thread class

}; // ThreadIf

}}}  // end namespace gz::common::thread

#endif // GZ_COMMON_THREADIF_H_

