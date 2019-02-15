
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
   #ifdef DEBUG
   printf("%s:%s:%d - top of translate_address 64\n",
		 __FILE__, "translate_address64()", __LINE__);
   #endif
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
        thread_t *t = malloc(sizeof(thread_t));

        mallocCheck(t, __LINE__);
        t->status = malloc(sizeof(state_t));

        mallocCheck(t->status, __LINE__);
        t->stack = malloc(STACK_SIZE);

        mallocCheck(t->stack, __LINE__);
        t->status->id = newId;
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
        appendThreadToList(t, threads);
        appendThreadToList(t, readyQ);
        
        printf("%s:%s:%d - CreateThread succeeded returning %d\n", __FILE__, "CreateThread()", __LINE__, newId);
        
        return newId++;
    }

    return -1;
}

int appendThreadToList(thread_t *t, list_t *l)
{
    printf("%s:%s:%d - top of AppendThreadToList()\n", 
        __FILE__, "AppendThreadToList()", __LINE__);

    if(NULL == t)
    {
        printf("%s:%s:%d - thread is null, returning -1\n", __FILE__, "AppendThreadToList()", __LINE__);
        return -1;
    }

    if(NULL == l)
    {
        printf("%s:%s:%d - list is null, returning -1\n", __FILE__, "AppendThreadToList()", __LINE__);

        return -1;
    }

    node_t *n = l->head;
    node_t *new = malloc(sizeof(node_t));

    mallocCheck(new, __LINE__);
    
    new->thread = t;
    new->next = new->prev = NULL;
    
    if(NULL == n)
    {
        l->head = new;
    }
    else
    {
        while(NULL != n->next) n = n->next;
        n->next = new;
        new->prev = n;
    }

    l->size++;
    
    printf("%s:%s:%d - success, returning %d\n", __FILE__, "AppendThreadToList()", __LINE__, t->status->id);
    
    return t->status->id;
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