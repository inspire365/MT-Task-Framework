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



Improvement
-------------
Use boost::lockfree::queue can improve performance than the mutex lock version
TaskQueue. The following is the comparision of the two with Linux time command
while executing 10000000 tasks.

mutex lock TaskQueue version:
real	0m34.266s
user	0m19.800s
sys	1m22.050s

boost::lockfree::queue version task queue:
real	0m12.203s
user	0m17.943s
sys	0m17.663s

For more information, please visit:
<Writing Lock-Free Code: A Corrected Queue> http://www.drdobbs.com/parallel/writing-lock-free-code-a-corrected-queue/210604448?pgno=1
<Yet another implementation of a lock-free circular array queue>
http://www.codeproject.com/Articles/153898/Yet-another-implementation-of-a-lock-free-circular

try the example for yourself.

Advance Usage
-------------
You can also make use of the framework's flexibility to customize it.<br/>

1. Customize your own taskqueue.<br/>
   TaskQueue only provide the default firt-come-first-out style queue. You can implement the TaskQueueIf to create your own task queue, such as priority queue. You can also set the queue limit size and some other things.
2. Customize your own thread behavior.<br/>
   Just implement Thread interface and assembly it into <code>TaskThreadMgr::ConstructTaskThread()</code> and <code>TaskThreadMgr::DestroyTaskThread(TaskThread* thr)</code> will do.
3. For different business tasks. You can also fit this framework to different business requirments. For example, one is    heavy loaded business, others are not. Of course, we should not mix them together. You can instantiate one             task_thread_manager for one business to solve this issue.
4. Implement lock-free queue for the taskqueue for more high performance.

TODO
----
1. It can very easy to extend to support Windows. 


If you have any advices or improvement, Please tell me! Thanks!

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

