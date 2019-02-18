/**
 * PI Calculation 
 * Using Leibniz formula
 * Since PI = 4 * arctan(1).
 */

#include "piCalc.h"
/**
 * Function to calculate PI terms
 */
void piCalculation(thread_t *thread) {
    double partialSum = 0;
    int id = thread->id;
    printf("ID: %d",id);
    for(long i = (10 * id)/numThreads; i < (10*(id + 1))/numThreads;  i++)
    {
         printf("Index: %d",i);
         printf("TERM %f", term);
         double partialN =  term * ((double)i - 0.5);
         printf("X: %f\n",partialN);
         partialSum += 4.0 / (1.0 + partialN*partialN);
    }
    printf("SP %f\n",partialSum);

    partialValues[id]=partialSum;
}

