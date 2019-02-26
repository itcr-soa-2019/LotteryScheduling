#include "scheduler.h"

int getWinnerTicket(int maxRange) {
    return rand() % maxRange + MIN_TICKETS;
}

task_t* getWinnerTask(task_list_t *taskList, int winnerTicket) {
    if (taskList == NULL) {
        printf("Error while getting winner task.");
        return NULL;
    }

    int ticketSum = 0;
    task_t* currentTask;

    for (int i = 0; i < taskList->size; i++) {
        currentTask = getTaskByIndex(i, taskList);
        ticketSum += currentTask->tickets;
        if(ticketSum >= winnerTicket) {
            return currentTask;
        }
    }
    printf("Not found winner task with ticket %d", winnerTicket);
    return NULL;
}

scheduler_t* initScheduler(int operationMode, int totalTickets, task_list_t *taskList) {
    scheduler_t* scheduler = malloc(sizeof(scheduler_t));
    if (scheduler == NULL) {
        printf("Error while allocating memory for scheduler_t.");
        exit(0);
    }

    scheduler->operationMode = operationMode;
    scheduler->totalTickets = totalTickets;
    scheduler->taskList = taskList;
    scheduler->currentTask = NULL;

    return scheduler;
}

void startScheduling(scheduler_t* scheduler) {
    // init seed to get different random numbers every time the program runs
    srand(time(NULL));
    int winnerTicket;
    task_t* winnerTask;

    if (scheduler->taskList == NULL) {
        printf("No tasks to schedule.");
        exit(0);
    }

    // keep scheduling while there are still tasks to complete
    while (scheduler->taskList->size != 0) {
        // 1. get winner ticket
        winnerTicket = getWinnerTicket(scheduler->totalTickets);

        // 2. find winner task in list
        winnerTask = getWinnerTask(scheduler->taskList, winnerTicket);

        // 3. if scheduler->currentTask is not null, deallocate it and assign new current task with the winner

        // 4. execute current task until signal (from thread or from timer according to operationMode)

        // 5. check if the current task was completed to remove it from the scheduler task list

        // repeat

    }

}


// Returns the current task defined by the scheduler
task_t * getCurrentTask() {
    return getTaskAt(scheduler->taskList, currentIndex) ;
}

// This should be used in the non expropiative mode
void verifyCurrentThreadProgress(double progress){

}

// Starts the threads work using the current task 
/**
 * This is required to give the thread all the required context
 * */
void runThread() {
    task_t* currentTask =  getCurrentTask(scheduler);
    piCalculation(currentTask, verifyCurrentThreadProgress);
}