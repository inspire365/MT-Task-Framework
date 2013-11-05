#ifndef GZ_COMMON_TASKIF_H_
#define GZ_COMMON_TASKIF_H_

#include <string>

namespace gz { namespace common { namespace task {

/*! \class TaskIf
    \brief A TaskIf base class
 *
 *  A TaskIf base class works as a base class of command pattern
 *  For more information about command pattern, please visit:
 *  http://en.wikipedia.org/wiki/Command_pattern
 */
class TaskIf
{
public:

  /**
   * virtual destructor for inheritance
   */
  virtual ~TaskIf() { /* empty */}

  /**
   * Override this function to implement your specific logic
   * @param thread_context  thead's specific context
   * @param app_context    application specific context
   */
  virtual void Execute(
    void* thread_context,
    void* app_context) = 0;

  /**
   * Release relative resource of this task
   * It's the User's responsibility to release
   * the resource
   */
  virtual void Release() = 0;

protected:

  TaskIf() { /* empty */ }

};  // TaskIf

}}} // namespace ::gz::common::task

#endif // GZ_COMMON_TASKIF_H_

