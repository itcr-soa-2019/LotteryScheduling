#include "scheduler.h"

int getWinnerTicket(int maxRange) {
    return rand() % maxRange + MIN_TICKETS;
}

task_t* getWinnerTask(task_list_t *taskList, int winnerTicket) {
    if (taskList == NULL) {
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
    for(int i = 0; i < 3; i++) {//while (scheduler->taskList->size != 0) {
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
