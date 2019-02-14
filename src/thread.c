
#include "thread.h"

// Constans definitions
#define PI 3.14159265
#define JB_SP 6
#define JB_PC 7

// variables declarations
list_t *threads = NULL;
list_t *readyQ = NULL;
unsigned int newID = 0; // unsigned to force newID to be positive

// Functions implementations
int CreateThread(void (*f) (void))
{
    if(numNodes(threads) < MAX_THREADS)
    {
        // allocate memory for thread 
        thread_t *t = malloc(sizeof(thread_t));

        MallocCheck(t, __LINE__);
        t->status = malloc(sizeof(state_t));

        MallocCheck(t->status, __LINE__);
        t->stack = malloc(STACK_SIZE);

        MallocCheck(t->stack, __LINE__);
        t->status->id = newID;
        t->status->num_runs = 
                t->status->total_exec_time = 
            t->status->total_sleep_time = 
            t->status->total_wait_time = 0; 
            t->status->avr_exec_time = 
            t->status->avr_wait_time = -1;

        t->status->priority = rand()%5 + 1; 
        
        printf("%s:%s:%d - thread id: %d with pri %d\n", __FILE__, "CreateThread()", __LINE__, t->status->id, t->status->priority);
        
        t->status->awake_after = -1;
        t->status->threadState = READY;
        
        // setjmp jmpbuf
        t->sp = (address_t)t->stack + STACK_SIZE - sizeof(address_t);
        t->pc = (address_t)f;
        
        sigsetjmp(t->jmpbuf, 1);
        (t->jmpbuf->__jmpbuf)[JB_SP] = translate_address(t->sp);
        (t->jmpbuf->__jmpbuf)[JB_PC] = translate_address(t->pc);
        
        sigemptyset(&t->jmpbuf->__saved_mask);
        
        printf("%s:%s:%d - location of function = %p\n", __FILE__, "CreateThread()", __LINE__, (void *)f);
        
        // manipulate jmpbuf sp and pc
        AppendThreadToList(t, threads);
        AppendThreadToList(t, readyQ);
        
        printf("%s:%s:%d - CreateThread succeeded returning %d\n", __FILE__, "CreateThread()", __LINE__, newID);
        
        return newID++;
    }

    return -1;
}

unsigned int numNodes(list_t *threads)
{
   if(NULL == threads) return 0;
   return threads->size;
}

/**
 * Function used to calculate the arc tangent of Pi, which is the
 * threads work to execute in the scheduler. The formula is:
 * arctan(1) = π/4, so 4 arctan(1) = π.
 */
void calculateArcTangent()
{    
    double param, result;

    param = 1.0;
    result = atan(param) * 180 / PI;
    
    printf("The arc tangent of %lf is %lf degrees\n", param, result);
}