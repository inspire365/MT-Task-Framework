#include "exampletask.h"
#include <stdio.h>


void ExampleTask::Execute(
    void* thread_context,
    void* app_context)
{
  printf("thread pointer: %p, ExampleTask value: %d\n", thread_context, value);
}

void ExampleTask::Release()
{
  delete this;
}

