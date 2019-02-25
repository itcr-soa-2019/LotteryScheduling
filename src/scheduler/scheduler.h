#ifndef scheduler_h
#define scheduler_h
#include "../threads/thread.h"
#include "../scheduler/task.h"


typedef struct
{
   int operationMode; // expropiative = 1   nonexpropiative = 0
   task_list_t *taskList;
   task_t *currentTask; // task being executed
   thread_t** threads;
    long numThreads;
    long currentThread;
    int preemptive;
    long completedThreads;
    int playingTickets;
    double yieldPercentage;
    sigjmp_buf context;
    int scheduleComplete;

}scheduler_t;

extern scheduler_t* Scheduler;


int Scheduler_SaveOwnContext(scheduler_t* Scheduler); //saves the context of the scheduler
void Scheduler_ResumesOwnContext(scheduler_t* Scheduler); //resumes the context of the scheduler
void Scheduler_Init(long numThreads, void* function, int preemptive, double yiedlPercentage, long* tickets, long* work);
void Scheduler_Free(scheduler_t* Scheduler);
int  Scheduler_SaveThread(scheduler_t* Scheduler); //saves current thread context
void Scheduler_ResumeThread(scheduler_t* Scheduler); //resumes current thread
void Scheduler_Schedule(scheduler_t* Scheduler);
void Scheduler_ThreadCompletes(scheduler_t* Scheduler);
void Scheduler_SwitchThreads(scheduler_t* Scheduler);
void Scheduler_SaveResult(scheduler_t* Scheduler, double result);
long Scheduler_GetWorkOfCurrentThread(scheduler_t* Scheduler);




// Initialize scheduling instance
void initScheduling(int operationMode, task_list_t *taskList);

// Selects from taskList the next task to be processed (lottery winner)
task_t *allocateNextTask();

// Removes task from the current task list
void completeTask(int pid);



#endif 


