#include "task.h"

task_t* initTask(int tickets, int workUnits, int quantumSize,  double progress, thread_t *thread) {
    task_t *task = malloc(sizeof(task_t));
    task->tickets = tickets;
    task->workUnits = workUnits;
    task->quantumSize = quantumSize;
    task->progress = progress;
    task->thread = thread;
    task->next = NULL;

    return task;
}

task_list_t* initTaskList() {
    task_list_t* taskList = malloc(sizeof(task_list_t));    

    if(taskList == NULL) {
        printf("Error while allocating memory for task_list_t.");
        exit(0);
    }
    taskList->head = NULL;
    taskList->last = NULL;

    return taskList;
}

int appendTask(task_t *task, task_list_t *list) {
    if (task == NULL || list == NULL) {
        printf("Error while appending task to task_list_t.");
        return -1;
    }

    // empty list
    if(list->head == NULL) {
        list->head = task;
        list->last = task;
    } else {
        list->last->next = task;
        list->last = task;
    }
    return 0;
}

task_t * getTaskAt(int index) {
    
    struct task_t* current = global_task_list->head; 
      
     // the index of the  
     // node we're currently 
     // looking at 
    int count = 0; 
    while (current != NULL) 
    { 
        if (count == index) 
            return(current); 
        count++; 
        current = current->next; 
    } 
    return NULL;
}

//todo: add method to deallocate memory --> free(pointer)