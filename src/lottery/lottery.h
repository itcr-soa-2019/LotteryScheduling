#include "../execution/execution.h"
#include "../threads/thread.h"
#include "../scheduler/task.h"
#include "../jobs/piCalc.h"

#ifndef lottery_h
#define lottery_h

typedef struct lottery_t
{
   int operationMode; 
   thread_t** threads;
   thread_t* currentThread;
   int totalTickets;
   double cpuYieldPercentage;
} lottery_t;

lottery_t testScheduler;

// the index of the current task in execution
int currentIndex;

// init lottery scheduling
void initLotterySchedule(void *function);

// start lottery scheduling
void startLotterySchedule();

// Returns the current task in execution
task_t * getCurrentTask();

// Starts the threads work using the current task 
void runThread();

#endif
