#include "task.h"
//#include "../jobs/piCalc.h"

#ifndef scheduler_h
#define scheduler_h

#define MIN_TICKETS 1

typedef struct scheduler_t
{
   int operationMode; // expropiative = 1   nonexpropiative = 0
   int totalTickets;
   task_list_t *taskList;
   task_t *currentTask; // task being executed
} scheduler_t;

// A pointer to the current scheduler sctruct
scheduler_t* scheduler;

// Initialize scheduling instance
void initScheduler(int operationMode, int totalTickets, task_list_t *taskList);

// Start scheduling tasks
void startScheduling(scheduler_t* scheduler);

// Selects from taskList the next task to be processed (lottery winner)
task_t* allocateNextTask();

// Removes task from the current task list
void completeTask(int pid);

#endif
