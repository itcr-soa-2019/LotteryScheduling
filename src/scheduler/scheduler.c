#include "scheduler.h"
#include "timer.h"

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

// Triggered when the timer alarm completes. Schedules a new task to be executed.
void allocateNextTask() {
    // check if progress is 100% and delete from task list
    if (scheduler->currentTask != NULL && scheduler->currentTask->progress == 1) {
        printf("Task COMPLETED-> %d.\n", scheduler->currentTask->id);
        deallocateCurrentTask();
    }

    // schedule new task
    if (scheduler->taskList->size > 0) {
        // 1. get winner ticket
        int winnerTicket = getWinnerTicket(scheduler->totalTickets);

        // 2. find winner task in list and assign new current task
        scheduler->currentTask = getWinnerTask(scheduler->taskList, winnerTicket);
        printf("Will now run Task-> %d.\n", scheduler->currentTask->id);

        // set new alarm for the selected current task
        setTimerAlarm(scheduler->currentTask->quantumSize); 
    } else {
        printf("No tasks left to schedule.\n");
    }
    
}

// This method is intercepted by allocateNextTask() when the timer alarm completes
void executeTasks() {
    if (scheduler->taskList == NULL ) {
        printf("No tasks to schedule.");
        exit(0);
    }

    // keep processing while there are still tasks to complete
    while (scheduler->taskList->size != 0) {
        // 4. execute current task until signal (from thread or from timer according to operationMode)
        // ToDo: agregar validación en piCalc para que no ejecute nada si el progreso del task ya se completó, para que le de tiempo a la tarea de completar su quantum en este ciclo.
        //executeTask(scheduler->currentTask);
        printf("Executing Task %d.\n", scheduler->currentTask->id);
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
        allocateNextTask(); //to select the first task to run
    }
    executeTasks(); //while durante el que se ejecuta el programa y durante ese tiempo se van a estar seteando alarmas
}

