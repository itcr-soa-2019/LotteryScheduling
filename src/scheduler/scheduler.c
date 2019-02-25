// Scheduler methods implementations here
#include "scheduler.h"

scheduler_t* Scheduler;


//Free any allocated memory of the lotery scheduler and the Loader
void Scheduler_Free(scheduler_t* this){
    int i = 0;
    for(; i< this->numThreads; i++){
        free(this->threads[i]);
    }
    free(this->threads);
    free(this);
}

//Creates a new Lotery Scheduler
void Scheduler_Init(long numThreads, void* function, int preemptive, double yiedlPercentage, long* tickets, long* work){
    long i = 0;
    Scheduler = (scheduler_t*) (malloc(sizeof(scheduler_t)));
    Scheduler->scheduleComplete = 0;
    Scheduler->numThreads = numThreads;
    Scheduler->currentThread = -1; //no current thread yet
    Scheduler->preemptive = preemptive;
    Scheduler->completedThreads = 0;
    Scheduler->yieldPercentage = yiedlPercentage;
    Scheduler->playingTickets = 0;
    srand((unsigned int)time(NULL));

    Scheduler->threads = (thread_t **) (malloc(numThreads * sizeof(thread_t*)));

    for (; i < numThreads; i++){
        Scheduler->threads[i] = Thread_New(i, function, tickets[i], work[i], yiedlPercentage);
        Scheduler->playingTickets += Scheduler->threads[i]->tickets;
    }
}

// Saves the current thread sigjmp_buf jmpbuf
int Scheduler_SaveThread(scheduler_t* this){
    return sigsetjmp(this->threads[this->currentThread]->jmpbuf, 1);
}

// Resumes the execution of the current thread to the last call of Scheduler_SaveThread, for the same threadId
void Scheduler_ResumeThread(scheduler_t* this) {
    if(this->preemptive){
        set_next_alarm();
    }
    if(Scheduler->scheduleComplete == 1){
        siglongjmp(this->threads[this->currentThread]->jmpbuf, 1);
    }

}

// The main method of the scheduler
void Scheduler_Schedule(scheduler_t* this){
    int index;
    long ticketSum = 0;

    if(this->completedThreads == this->numThreads){
        Scheduler_ResumesOwnContext(this);
    }

    if(this->currentThread != -1){
        int returnValue =  sigsetjmp(Scheduler->threads[Scheduler->currentThread]->jmpbuf, 1); //LoteryScheduler_SaveThread(Scheduler);
        if (returnValue == 1) {
            return;
        }
    }

    int random = rand() % this->playingTickets;

    for(index = 0; index < this->numThreads; index++){
        if(!this->threads[index]->status){
            ticketSum += this->threads[index]->tickets;
            if(ticketSum > random){
                break;
            }
        }
    }
    this->currentThread = index;
    Scheduler->scheduleComplete = 1;
    if(this->completedThreads < this->numThreads) {
        Scheduler_ResumeThread(this);
    }
}

// Sets the current thread to completed and calls scheduler_t
void Scheduler_ThreadCompletes(scheduler_t* this){
    this->threads[this->currentThread]->status = 5; // Note: review this based on the  state_t *status defined in the thread.h
    printf("Thread completed: %ld\n", this->currentThread);
    this->completedThreads++;
    this->playingTickets -= this->threads[this->currentThread]->tickets;
    Scheduler_Schedule(this);
}

//saves the context of the scheduler
int Scheduler_SaveOwnContext(scheduler_t* this){
    return sigsetjmp(this->context, 1);
}

//saves the context of the scheduler
void Scheduler_ResumesOwnContext(scheduler_t* this){
    siglongjmp(this->context, 1);
}

//gets the units of workUnits of the current thread
long Scheduler_GetWorkOfCurrentThread(scheduler_t* this){
    return this->threads[this->currentThread]->workUnits;
}