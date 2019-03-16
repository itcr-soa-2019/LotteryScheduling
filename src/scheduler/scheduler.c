#include "scheduler.h"
#include "timer.h"
#include "../jobs/piCalc.h"

int getWinnerTicket(int maxRange) {
    if (maxRange > 0) {
        return rand() % maxRange + MIN_TICKETS;
    } else {
        printf("Error while getting winner ticket.");
        exit(1);
    }
}

task_t* getWinnerTask(task_list_t *taskList, int winnerTicket) {
    if (taskList == NULL || taskList->size == 0) {
        printf("Error while getting winner task.");
        return NULL;
    }

    task_t* task = taskList->head;
    int ticketSum = 0;

    while (task != NULL)
    {
        ticketSum += task->tickets;
        if(ticketSum >= winnerTicket) {
            return task;
        }
        task = task->next;
    }
    printf("Not found winner task with ticket %d", winnerTicket);
    return NULL;
}

// Removes current task from scheduler's list
void deallocateCurrentTask() {
    scheduler->totalTickets -= scheduler->currentTask->tickets;
    removeTask(scheduler->currentTask, scheduler->taskList);
    scheduler->currentTask = NULL;
}

// Schedules a new task to be executed.
// In expropiative mode, this method is triggered when the timer alarm completes. 
void allocateNextTask() { 
    
    // check if progress is 100% and delete from task list
    if (scheduler->currentTask != NULL && scheduler->currentTask->progress == 1) {
        printf("Task COMPLETED-> %d.\n", scheduler->currentTask->thread->id);
        deallocateCurrentTask();
    }

    // schedule new task
    if (scheduler->taskList->size > 0) {
        // 1. before selecting a new current task, save the thread context of the previous
        if (scheduler->currentTask != NULL) {
            //printf("progress: %f, id: %d\n", scheduler->currentTask->progress, scheduler->currentTask->thread->id);
            printf("SAVE %p.\n", scheduler->currentTask->thread);
            saveThread(scheduler->currentTask->thread);
        } 
    
        // 2. get winner ticket
        int winnerTicket = getWinnerTicket(scheduler->totalTickets);
    
        // 3. find winner task in list and assign new current task
        scheduler->currentTask = getWinnerTask(scheduler->taskList, winnerTicket);

        printf("Will now run Task-> %d.\n", scheduler->currentTask->thread->id);

        // set new alarm for the selected current task
        if (scheduler->operationMode == 1) {
            setTimerAlarm(scheduler->currentTask->quantumSize);
        }

        // 4. resume thread to start its execution
        printf("RESUME %p.\n", scheduler->currentTask->thread);
        Resume_Thread(scheduler->currentTask->thread);
    } else {
        printf("No tasks left to schedule.\n");

        for(int x= 0; x< 2; x++)
        {
            calculated_pi += partialValues[x];
            printf("%f\n",partialValues[x]);
        }
    printf("PI:%f\n", (double)calculated_pi * 4.0);

        exit(0);
    } 
}

// Used only for the non expropiative mode. 
// Progress is updated for the current task by piCalc, every time a workunit is completed.
void verifyCurrentThreadProgress(double progress){
    if (scheduler->operationMode == 0) {
        printf("Task %d progress: %f\n", scheduler->currentTask->thread->id, scheduler->currentTask->progress);
        if (scheduler->currentTask->progress >= scheduler->currentTask->cpuYieldPercentage) { //el CPUYield percentage tiene que tomar en cuenta las diferentes iteraciones del progress, sino en la segunda siempre se va a cumplir esta condicion
            scheduler->currentTask->cpuYieldPercentage += scheduler->currentTask->thread->cpuYieldPercentage;
            allocateNextTask();
        }   
    }
}

void runThread() {
    while(1) {
        printf("Executing Task %d.\n", scheduler->currentTask->thread->id);
        piCalculation(scheduler->currentTask, verifyCurrentThreadProgress);
    }
}

void initScheduler(int operationMode, int totalTickets, task_list_t *taskList) {
    scheduler = malloc(sizeof(scheduler_t));
    if (scheduler == NULL) {
        printf("Error while allocating memory for scheduler_t.");
        exit(1);
    }
    scheduler->operationMode = operationMode;
    scheduler->totalTickets = totalTickets;
    scheduler->taskList = taskList;
    scheduler->currentTask = NULL;

    // init array of partial pi values
    partialValues = calloc(sizeof(double), scheduler->taskList->size);

    // init seed to get different random numbers for winner ticket every time the program runs
    srand(time(NULL));

    // Setup timer
    if (scheduler->operationMode == 1) {
        setupTimer(allocateNextTask);
    }
    allocateNextTask(); //to select the first task to run

    if (scheduler->operationMode == 1) {
        //executeTasks(); 
    }

    printf("FINAAAAL");
}

