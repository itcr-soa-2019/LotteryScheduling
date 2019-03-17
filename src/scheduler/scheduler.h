#include "task.h"
#include "../ui/ui_functions.h"

#ifndef scheduler_h
#define scheduler_h

#define MIN_TICKETS 1

GtkBuilder *builder;

typedef struct scheduler_t
{
   int operationMode; // expropiative = 1   nonexpropiative = 0
   int totalTickets;
   int totalThreads;
   task_list_t *taskList;
   volatile task_t *currentTask; // task being executed
} scheduler_t;

// A pointer to the current scheduler sctruct
volatile scheduler_t* scheduler;

// Initialize and start scheduling tasks
void initScheduler(int operationMode, int totalTickets, int numThreads, task_list_t *taskList);

void runThread();

// Removes current task from scheduler's list
void deallocateCurrentTask();

#endif
