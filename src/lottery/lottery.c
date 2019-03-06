#include "lottery.h"
// init lottery scheduling
void initLotterySchedule(void *function)
{        
    struct execution exec = executor;
    testScheduler.totalTickets = 0; 
    testScheduler.operationMode = exec.operationMode;       
    testScheduler.cpuYieldPercentage = exec.cpuYieldPercentage;
    testScheduler.threads = (thread_t **) (malloc(exec.numThreads * sizeof(thread_t*)));
    
    for(int i = 0; i < exec.numThreads; i++)
    {
        long tickets = exec.tickets[i];
        long workUnits = exec.workUnits[i];
        testScheduler.threads[i] = createThread(function, tickets, workUnits, exec.cpuYieldPercentage);
        testScheduler.totalTickets += testScheduler.threads[i]->tickets;
    }
}

// start lottery scheduling
void startLotterySchedule()
{

}

void runThread(){

}
