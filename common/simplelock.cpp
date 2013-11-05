#include "simplelock.h"
#include <cassert>
#include <new>
#include <stdexcept>

namespace gz { namespace common { namespace concurrency {

SimpleLock::SimpleLock()
{
  int err = ::pthread_mutex_init( &mutex_, NULL );
  assert( !err );
  if ( err )
  {
    throw std::bad_alloc();
  }
}

SimpleLock::~SimpleLock()
{
#ifndef NDEBUG
  int err =
#endif// #ifndef NDEBUG
  ::pthread_mutex_destroy( &mutex_ );
#ifndef NDEBUG
  assert( !err );
#endif// #ifndef NDEBUG
}

void SimpleLock::Lock()
{
  int err = ::pthread_mutex_lock( &mutex_ );
  assert( !err );
  if ( err )
  {
    throw std::runtime_error( "Failed to lock." );
  }
}

void SimpleLock::Unlock()
{
#ifndef NDEBUG
  int err =
#endif// #ifndef NDEBUG  
  ::pthread_mutex_unlock( &mutex_ );
#ifndef NDEBUG
  assert( !err );
#endif// #ifndef NDEBUG  
}

}}} // ::gz::common::concurrency

