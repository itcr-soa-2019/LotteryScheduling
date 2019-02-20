/**
 * PI Calculation
 * Using Leibniz's Series
 */

#include "piCalc.h"
#define TermsPerUnit 50

/**
 * Function to calculate PI terms
 */
void piCalculation(thread_t *thread) {
    double partialSum = 0;
    double lastValue = 0;
    int id = thread->id;
    int workUnits = 100;
    double startPoint = id * workUnits * TermsPerUnit;
    for(long i = 0; i < workUnits;  i++)
    {
         calculateWorkUnit((i*TermsPerUnit)+startPoint, &partialSum);
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

