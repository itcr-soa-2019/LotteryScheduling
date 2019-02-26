#include "lottery.h"
// init lottery scheduling
void initLotterySchedule(void *function)
{        
    struct execution exec = executor;
    scheduler.totalTickets = 0; 
    scheduler.operationMode = exec.operationMode;       
    scheduler.cpuYieldPercentage = exec.cpuYieldPercentage;
    scheduler.threads = (thread_t **) (malloc(exec.numThreads * sizeof(thread_t*)));
    
    for(int i = 0; i < exec.numThreads; i++)
    {
        long tickets = exec.tickets[i];
        long workUnits = exec.workUnits[i];
        scheduler.threads[i] = createThread(function, tickets, workUnits, exec.cpuYieldPercentage);
        scheduler.totalTickets += scheduler.threads[i]->tickets;
    }
}

// start lottery scheduling
void startLotterySchedule()
{

}
