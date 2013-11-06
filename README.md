Multi Thread Task Framework
===========================
A C++ Multi Thread Task Framework<br/>
MT-Task-Framework is a C++ multi-thread task framework under Linux. With the help of this framework, you can wrapper different tasks uniformly in the multi thread framework with only a few effort. The framework also provide flexiblity for you to customize the thread and task queue behaviors.


General Usage and API
---------------------

In most of the case, the basic functionality of this framework will meet your requirement. Just take the following simple steps to use:

1. Implement the TaskIf interfaces to make your task execution in:<br/>
<code>virtual void Execute( void* thread_context,  void* app_context)=0;<br/>
virtual void Release() = 0;</code>
2. Setup the default components of the framework and make it run:<br/>
<pre><code>TaskQueue task_queue;      // the task queue for your tasks
TaskThreadMgr task_thread_manager(5, task_queue); // the number to tell how many thread to create
task_thread_manager.Init();    // should always call Init() and then Start()
  task_thread_manager.Start();   // make all threads running</code></pre>
3. Generate your tasks and push them to the queue, the task will execute automatically:
<code>task_queue.Push(task)</code>
4. If you need to terminate the framework:<br/>
<pre><code>task_thread_manager.Stop();
task_thread_manager.Term();
</code></pre>
  should always call in the order first Stop() and then Term(). In some situation that the worker thread may wait for some task so that it can not stop immediatly, you can push some NullTask to wake the worker threads wake to exit.


Advance Usage
-------------
You can also make use of the framework's flexibility to customize it.<br/>

1. Customize your own taskqueue.<br/>
   TaskQueue only provide the default firt-come-first-out style queue. You can implement the TaskQueueIf to create your own task queue, such as priority queue. You can also set the queue limit size and some other things.
2. Customize your own thread behavior.<br/>
   Just implement Thread interface and assembly it into <code>TaskThreadMgr::ConstructTaskThread()</code> and <code>TaskThreadMgr::DestroyTaskThread(TaskThread* thr)</code> will do.


TODO
----
It can very easy to extend to support Windows. If you have any advices or improvement, Please tell me! Thanks!


Acknowledgments
---------------
Two common files(autodone & simplelock) were wrote by my colleague Mr. Yang. I do not want to reinvent ones, Thanks!



License
-------
Copyright (C) 2013

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

           By Dan

Thanks!

