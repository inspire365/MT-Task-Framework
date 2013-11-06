Multi Thread Task Framework
===========================
A C++ Multi Thread Task Framework
MT-Task-Framework is a C++ multi-thread task framework under Linux. With the help of this framework, you can wrapper different tasks uniformly in the multi thread framework with only a few effort. The framework also provide flexiblity for you to customize the thread and task queue behaviors.


General Usage and API
---------------------

In most of the case, the basic functionality of this framework will meet your requirement. Just take the following simple steps to use:

1. Implement the TaskIf interfaces to make your task execution in:
<code>virtual void Execute( void* thread_context,  void* app_context)=0; </code>
<code>virtual void Release() = 0;</code>
2. Setup the default components of the framework and make it run:
<code>
  TaskQueue task_queue;      // the task queue for your tasks
  TaskThreadMgr task_thread_manager(5, task_queue); // the number to tell how many thread to create
  task_thread_manager.Init();    // should always call Init() and then Start()
  task_thread_manager.Start();   // make all threads running
</code>
3. Generate your tasks and push them to the queue, the task will execute automatically:
<code>task_queue.Push(task)</code>
4. If you need to terminate the framework:
<code>
  task_thread_manager.Stop();
  task_thread_manager.Term();
</code>
  should always call in the order first Stop() and then Term(). In some situation that the worker thread may wait for some task so that it can not stop immediatly, you can push some NullTask to wake the worker threads wake to exit.


Advance Usage
-------------
You can also make use of the framework's flexibility to customize it.

1. Customize your own taskqueue.
   TaskQueue only provide the default firt-come-first-out style queue. You can implement the TaskQueueIf to create your own task queue, such as priority queue. You can also set the queue limit size and some other things.
2. Customize your own thread behavior.
   Just implement Thread interface and assembly it into <code>TaskThreadMgr::ConstructTaskThread()</code> and <code>TaskThreadMgr::DestroyTaskThread(TaskThread* thr)</code> will do.

