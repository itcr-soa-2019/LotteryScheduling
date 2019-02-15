
#include "jobs.h"


// Constans definitions
#define PI 3.14159265

/**
 * Function used to calculate the arc tangent of Pi, which is the
 * threads work to execute in the scheduler. The formula is:
 * arctan(1) = π/4, so 4 arctan(1) = π.
 */
void calculateArcTangent(void)
{    
    double param, result;

    // infinity loop so threads dont stop
    while(1)
    {
        param = 1.0;
        result = atan(param) * 180 / PI;        
        printf("The arc tangent of %lf is %lf degrees\n", param, result);
    }
}