#include <iostream>
#include "exampletask.h"
#include <taskif.h>
#include <nulltask.h>
#include <taskqueue.h>
#include <taskthreadmgr.h>

using ::gz::common::task::TaskIf;
using ::gz::common::task::NullTask;
using ::gz::common::task::TaskQueue;
using ::gz::common::task::TaskThreadMgr;

using ::std::cout;
using ::std::endl;

int main(int argc, char** argv)
{

  TaskQueue task_queue;
  TaskThreadMgr task_thread_manager(5, task_queue);
  task_thread_manager.Init();
  task_thread_manager.Start();   // make all threads running
  cout << "------------------------begin test------------------------------" << endl;
  TaskIf* tk = NULL;
  for (int i = 0 ; i < 10; ++i )
  {
    tk = new ExampleTask(i);
    task_queue.Push(tk);
  }


  sleep(10);
  cout << "---------------------- stop thread manager ------------------------------" << endl;
  // push these tasks to wake the thread to stop
  task_thread_manager.Stop();
  for (int i = 0 ; i < 5; ++i )
  {
    tk = new NullTask();
    task_queue.Push(tk);
  }
  cout << "---------------------- term thread manager ------------------------------" << endl;
  task_thread_manager.Term();

  return 0;
}





