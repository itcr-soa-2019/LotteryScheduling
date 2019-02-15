
#include "thread.h"

// Constans definitions
#define PI 3.14159265
#define JB_SP 6
#define JB_PC 7

// variables declarations
list_t *threads = NULL;
list_t *readyQ = NULL;
unsigned int newId = 0; // unsigned to force newId to be positive

// 
address_t translate_address(address_t addr)
{   
    address_t ret;
    asm volatile("xor    %%fs:0x30,%0\n"
        "rol    $0x11,%0\n"
                : "=g" (ret)
                : "0" (addr));
    return ret;
}

// create a new thread and return the pid
int createThread(void (*f) (void))
{
    if(numNodes(threads) < MAX_THREADS)
    {
        // allocate memory for thread 
        thread_t *thread = malloc(sizeof(thread_t));

        mallocCheck(thread, __LINE__);
        thread->status = malloc(sizeof(state_t));

        mallocCheck(thread->status, __LINE__);
        thread->stack = malloc(STACK_SIZE);

        mallocCheck(thread->stack, __LINE__);
        thread->status->id = newId;
        thread->status->num_runs = 
        thread->status->total_exec_time = 
        thread->status->total_sleep_time = 
        thread->status->total_wait_time = 0; 
        thread->status->avr_exec_time = 
        thread->status->avr_wait_time = -1;

        thread->status->priority = rand()%5 + 1; 
        
        printf("Thread id: %d with pri %d\n", thread->status->id, thread->status->priority);
        
        thread->status->awake_after = -1;
        thread->status->threadState = READY;
        
        // setjmp jmpbuf
        thread->sp = (address_t)thread->stack + STACK_SIZE - sizeof(address_t);
        thread->pc = (address_t)f;
        
        sigsetjmp(thread->jmpbuf, 1);
        (thread->jmpbuf->__jmpbuf)[JB_SP] = translate_address(thread->sp);
        (thread->jmpbuf->__jmpbuf)[JB_PC] = translate_address(thread->pc);
        
        sigemptyset(&thread->jmpbuf->__saved_mask);
        
        // manipulate jmpbuf sp and pc
        appendThread(thread, threads);
        appendThread(thread, readyQ);
        
        printf("createThread succeeded returning %d\n", newId);
        
        return newId++;
    }

    return -1;
}

// evaluates if the thread and list are not null 
// in order to make succesfull apend on list
int evalThreadAppend(thread_t *thread, list_t *list)
{
    if(NULL == thread)
    {
        printf("\nThread is null, returning -1\n");
        return -1;
    }

    if(NULL == list)
    {
        printf("\nList is null, returning -1\n");
        return -1;
    }

    return 1;
}

// add a thread to one of two lists used
// threads and readyQ are used in the createThread function
int appendThread(thread_t *thread, list_t *list)
{
    if ( ! evalThreadAppend(thread, list) == 1)
    {
        return -1;
    }

    node_t *node = list->head;
    node_t *new = malloc(sizeof(node_t));

    mallocCheck(new, __LINE__);
    
    new->thread = thread;
    new->next = new->prev = NULL;
    
    if(NULL == node)
    {
        list->head = new;
    }
    else
    {
        while(NULL != node->next) node = node->next;
        node->next = new;
        new->prev = node;
    }

    list->size++;
    
    printf("Success adding thread to list, returning %d\n", thread->status->id);
    
    return thread->status->id;
}

// return the number of threads contained in the thread list
unsigned int numNodes(list_t *threads)
{
    if(NULL == threads) return 0;
    return threads->size;
}

// check if memory allocation is null
void mallocCheck(void *pointer, int lineNumber)
{
    if(NULL != pointer) return;

    printf("malloc returned NULL at line %d in \"%s\"", lineNumber, __FILE__);
    abort();
}

// initialize temporal list to store threads
void initLists()
{
    threads = malloc(sizeof(list_t));
    mallocCheck(threads, __LINE__);
    threads->head = NULL;
    threads->size = 0;

    readyQ = malloc(sizeof(list_t));
    mallocCheck(readyQ, __LINE__);
    readyQ->head = NULL;
    readyQ->size = 0;

    srand(time(NULL));

    printf("Lists have been created\n");   
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