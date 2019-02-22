#include "../execution/execution.h"
#include "../threads/thread.h"

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

lottery_t scheduler;

// init lottery scheduling
void initLotterySchedule(void *function);

// start lottery scheduling
void startLotterySchedule();

#endif
