/**
 * PI Calculation
 * Using Leibniz's Series
 */


#include "piCalc.h"
/**
 * Function to calculate PI terms
 */
void piCalculation(task_t *task, void (*reportProgress)(double)) {
    double partialSum = 0;
    double lastValue = 0;
    int id = task->thread->id;
    int workUnits = task->workUnits;
    double startPoint = id * workUnits * TermsPerUnit;
    for(int i = 0; i < workUnits;  i++)
    {
         calculateWorkUnit((i*TermsPerUnit)+startPoint, &partialSum);
         double progress = ((double)i + 1.0) / (double) workUnits; // Calculates the current progress for this task
         task->progress = progress;
         reportProgress(progress);
    }
    partialValues[id]=partialSum;
}

// Used by the thread to see if the workUnit are completed or need to assign a new thread 
void  reportProgress(progress) {
    // check if progress is 100% and delete from task list
    task_t *task;
    int id = task->thread->id;
    if (task->currentThread != NULL && task->progress == 1) {
        printf("Task COMPLETED-> %d.\n", task->id);
        deallocateCurrentTask();
    }else{
        while (progress != 1){
            saveThread(task);
            // initLotterySchedule() or createThread or appendThread ?????

        }

    }

   
    
}


/**
 * Calculates a single workUnit.
 * A Work unit is equivalent to 50 terms of the 
 * geometric series.
 */
void calculateWorkUnit(int startIndex, double *partialSum) {
    for(int i = startIndex; i < (startIndex + TermsPerUnit); i++){        
        double v = pow(-1.0, (double) (i)) / (2.0*(double)(i)+1.0);
        *partialSum += v;
    }
}

