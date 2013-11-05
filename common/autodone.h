#ifndef GZ_UTILITY_AUTODONE_H_
#define GZ_UTILITY_AUTODONE_H_

namespace gz { namespace common { namespace utility {

/**
 * @class AutoDone
 *
 * guarantee to provide auto cleanup operation for a scope operation
 */
template< class T >
class AutoDone
{
public:

  typedef T task_type;

public:

  /**
   * Constructor
   * @param task object to operate on
   * @param todo the operation to be executed immediatly in the constructor if not NULL
   * @param done the operation to be executed in the destructor of the AutoDone
   */
  AutoDone(
    task_type& task,
    void ( task_type::*todo )(),
    void ( task_type::*done )()):
    task_( task ),
    do_( todo ),
    done_( done )
  {
    if ( NULL != do_ )
    {
      ( task_.*do_ )();
    }
  }

  /**
   * Destructor
   */
  ~AutoDone()
  {
    if ( NULL != done_ )
    {
      ( task_.*done_ )();
    }
  }

private:

  AutoDone();
  AutoDone( const AutoDone& );
  AutoDone& operator=( const AutoDone& );

private:

  task_type& task_;
  void ( task_type::*do_ )();
  void ( task_type::*done_ )();

};  // AutoDone

}}} // ::gz::common::utility

#endif// GZ_UTILITY_AUTODONE_H_

