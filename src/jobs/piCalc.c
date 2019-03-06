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

void reportProgress(double p) {
    printf("Percentage: %f", p);
}

/**
 * Start thread work
 */
void threadRun(){
    printf("****Thread Run: %f", 0.0);
    // piCalculation(currentTask,  reportProgress);
}

