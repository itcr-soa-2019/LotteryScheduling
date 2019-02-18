#ifndef scheduler_h
#define scheduler_h

typedef struct scheduler_t
{
   int operationMode; // expropiative = 1   nonexpropiative = 0
   task_list_t *taskList;
   task_t *currentTask; // task being executed
} scheduler_t;

// Initialize scheduling instance
void initScheduling(int operationMode, task_list_t *taskList);

// Selects from taskList the next task to be processed (lottery winner)
task_t *allocateNextTask();

// Removes task from the current task list
void completeTask(int pid);


#endif
