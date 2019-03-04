#include "scheduler.h"
#include "timer.h"

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

void allocateNextTask() {
    if (scheduler->currentTask != NULL) {
        printf("CurrentTask %d\n", scheduler->currentTask->id);
    }
    int winnerTicket;
    task_t* winnerTask;

    // 1. get winner ticket
     winnerTicket = getWinnerTicket(scheduler->totalTickets);

     // 2. find winner task in list and assign new current task
     winnerTask = getWinnerTask(scheduler->taskList, winnerTicket);
     scheduler->currentTask = winnerTask;
    printf("Will now run Task %d.\n", scheduler->currentTask->id);

    // set new alarm to keep scheduling tasks
    setTimerAlarm(scheduler->currentTask->quantumSize); 
}

// This method is intercepted by allocateNextTask() when the timer alarm completes
void schedule() {
    if (scheduler->taskList == NULL) {
        printf("No tasks to schedule.");
        exit(0);
    }

     // keep scheduling while there are still tasks to complete
     while (scheduler->taskList->size != 0) {
         // 4. execute current task until signal (from thread or from timer according to operationMode)
         executeTask(scheduler->currentTask);

         // 5. check if the current task was completed to remove it from the scheduler task list
         //(this step requires to schedule a new current task [allocateNextTask()])

         // repeat
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

    // init seed to get different random numbers for winner ticket every time the program runs
    srand(time(NULL));

    // Setup timer
    if (scheduler->operationMode == 1) {
        setupTimer(allocateNextTask);
        allocateNextTask();
    }
    schedule();
}

