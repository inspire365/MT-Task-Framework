#include "lockfreequeue.h"

namespace gz { namespace common { namespace task {

LockFreeQueue::LockFreeQueue(
    uint32_t queue_threshold = (1<<10),
    uint32_t queue_max_limit = (1<<11)):
    queue_threadhold_(queue_threshold),
    queue_max_limit_(queue_max_limit),
    queue_size_(0),
    queue_(queue_max_limit)
{
  // empty
}


}}} // ::gz::common::task

