#include "../threads/thread.h"

#ifndef task_h
#define task_h

typedef struct task_t
{
   int id;
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
   unsigned int size;
} task_list_t;

// initialize task element
task_t* initTask(int id, int tickets, int workUnits, int quantumSize, double progress, thread_t *thread);

// execute pi calculation
void executeTask(task_t *task);

// stop task execution
void stopTask(task_t *task);

// initialize new list of tasks
task_list_t* initTaskList();

// add new element to existing list of tasks
int appendTask(task_t *task, task_list_t *list);

// remove task from list
int removeTask(task_t *task, task_list_t *list);

#endif
