#include "../jobs/piCalc.h"
#include "task.h"

task_t* initTask(int id, int tickets, int workUnits, int quantumSize,  double progress, thread_t *thread,double cpuYieldPercentage) {
    task_t *task = malloc(sizeof(task_t));
    task->id = id;
    task->tickets = tickets;
    task->workUnits = workUnits;
    task->quantumSize = quantumSize;
    task->progress = progress;
    task->thread = thread;
    task->next = NULL;
    task ->cpuYieldPercentage = cpuYieldPercentage;

    return task;
}

// This should be used in the non expropiative mode
void verifyCurrentThreadProgress(double progress,task_t *task){

   if (task->progress >= task->cpuYieldPercentage) {
        printf("Allocate Next Task");
        saveThread(task->thread);
        allocateNextTask(); //to select another task to run
   }
    //executeTasks(); //while durante el que se ejecuta el programa y durante ese tiempo se van a estar seteando alarmas
  
}

void executeTask(task_t *task) {
    piCalculation(task, verifyCurrentThreadProgress);
}

void stopTask(task_t *task) {
    // stop pi calculation, update progress and workunits left for this task
}

task_list_t* initTaskList() {
    task_list_t* taskList = malloc(sizeof(task_list_t));    

    if (taskList == NULL) {
        printf("Error while allocating memory for task_list_t.");
        exit(0);
    }
    taskList->head = NULL;
    taskList->last = NULL;
    taskList->size = 0;

    return taskList;
}

int appendTask(task_t *task, task_list_t *list) {
    if (task == NULL || list == NULL) {
        printf("Error while appending task to task_list_t.");
        return -1;
    }

    // empty list
    if (list->head == NULL) {
        list->head = task;
        list->last = task;
    } else {
        list->last->next = task;
        list->last = task;
    }
    list->size ++;
    return 0;
}

/*
 * -1 = error removing task
 *  0 = success removing task
 */
int removeTask(task_t *task, task_list_t *list) {
    if (task == NULL || list == NULL) {
        printf("Error while removing task from task_list_t.");
        return -1;
    }

    // delete head
    if (task == list->head) {
        list->head = list->head->next;
        free(task);
        list->size--;
        return 0;
    }

    int i = 0;
    task_t* current = list->head->next;
    task_t* prev = list->head;
    while (current != NULL)
    {
        if (current == task) {
            prev->next = current->next;
            free(task);
            list->size--;
            return 0;
        }
        prev = current;
        current = current->next;
        i++;
    }
    printf("Error while removing unexistent task from task_list_t.");
    return -1;
}

task_t* getTaskByIndex(int index, task_list_t *list) {
    if (list == NULL) {
        printf("Error while getting task by index.");
        return NULL;
    }

    int i = 0;
    task_t* current = list->head;

    while (current != NULL)
    {
        if (i == index) {
            return current;
        }
        i++;
        current = current->next;
    }
    printf("Not found task at index %d", index);
    return NULL;
}

