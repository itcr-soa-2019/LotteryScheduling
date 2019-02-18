#include <stdio.h>
#include <stdlib.h>
#include "../threads/thread.h"

double series;
volatile double calculated_pi;
int numThreads;
double* partialValues;
double term;
/**
 * Function to calculate PI terms
 */
void piCalculation(thread_t *thread);