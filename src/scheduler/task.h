#include "../threads/thread.h"

#ifndef task_h
#define task_h

typedef struct task_t
{
   int tickets;
   int workUnits;
   int quantumSize; // millisecs if expropiative mode or work % if nonexpropiative mode
   double progress; // Indicates the current progress value of this task
   thread_t *thread;
   struct task_t *next;
} task_t;

typedef struct task_list_t
{
   task_t *head;
   task_t *last;
} task_list_t;

// initialize task element
task_t* initTask(int tickets, int workUnits, int quantumSize, double progress, thread_t *thread);

// initialize local list of tasks
task_list_t* initTaskList();

// add new element to the local tasks list
int appendTask(task_t *task, task_list_t *list);

//Global access to the array of tasks variable
volatile task_list_t * global_task_list;

// Return the task at nth index
task_t * getTaskAt(int index) ;


#endif
