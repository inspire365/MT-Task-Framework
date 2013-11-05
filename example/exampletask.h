#ifndef EXAMPLE_TASK_H_
#define EXAMPLE_TASK_H_

#include <taskif.h>

using ::gz::common::task::TaskIf;

class ExampleTask : public TaskIf
{
public:

  ExampleTask(int val):
    value(val) { }

  ~ExampleTask() { }

  virtual void Execute(
    void* thread_context,
    void* app_context);

  virtual void Release();

private:

  int value;

};  // ExampleTask

#endif // EXAMPLE_TASK_H_

