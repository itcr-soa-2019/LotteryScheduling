#include <stdio.h>
#include <stdlib.h>
#include "../threads/thread.h"
#include "../scheduler/task.h"

volatile double calculated_pi;
int numThreads;
double* partialValues;
#define TermsPerUnit 50

/**
 * Function to calculate PI terms
 */
void piCalculation(task_t *task, void (*verifyCurrentThreadProgress)(double,task_t *task));
void calculateWorkUnit(int startIndex, double *partialSum);