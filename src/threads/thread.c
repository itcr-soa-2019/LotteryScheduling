
#include "thread.h"

// 64 bit Intel arch
#define JB_SP 6
#define JB_PC 7

list_t *threads = NULL;
unsigned int newId = 0;


// Translation required when using an address of a variable
address_t translate_address(address_t address) {
    address_t ret;
    asm volatile("xor    %%fs:0x30,%0\n"
        "rol    $0x11,%0\n"
                : "=g" (ret)
                : "0" (address));
    return ret;
}

// create a new thread and return the pid
thread_t* createThread(void (*function) (void), long tickets, long workUnits, long cpuYield) {
    if ( ! ( numNodes(threads) < MAX_THREADS ) ) {
        return NULL;
    }
    
    thread_t *thread = malloc(sizeof(thread_t));
    thread->status = malloc(sizeof(state_t));
    thread->stack = malloc(STACK_SIZE);
    address_t sp, pc;

    thread->id = newId++;    
    thread->tickets = tickets;
    thread->workUnits = workUnits;
    thread->cpuYieldPercentage = cpuYield;
    thread->status->id = newId;    
    thread->status->num_runs = 
    thread->status->total_exec_time = 
    thread->status->total_sleep_time = 
    thread->status->total_wait_time = 0; 
    thread->status->avr_exec_time = 
    thread->status->avr_wait_time = -1;
    thread->status->priority = rand() % 5 + 1;
    thread->status->awake_after = -1;
    thread->status->threadState = READY;
    
    sp = (address_t) thread->stack + STACK_SIZE - sizeof(address_t);
    pc = (address_t) function;    

    sigsetjmp(thread->jmpbuf, 1);
    (thread->jmpbuf->__jmpbuf)[JB_SP] = translate_address(sp);
    (thread->jmpbuf->__jmpbuf)[JB_PC] = translate_address(pc);    
    sigemptyset(&thread->jmpbuf->__saved_mask);
    printf("%s:%s:%d - location of function = %p\n", __FILE__, "CreateThread()", __LINE__, (void *)function);
    printf("Thread created, id: %d\n", newId);
    return thread;
}


// Saves the thread execution context
int saveThread(thread_t* thread) {
    return sigsetjmp(thread->jmpbuf, 1);
}

// Resumes thread
void Resume_Thread(thread_t* thread) {
    printf("spawn thread: %ld", (thread->jmpbuf->__jmpbuf)[JB_PC]);
    siglongjmp(thread->jmpbuf, 1);
    printf("Esto NO DEBERIA SALIR");

}

// evaluates if the thread and list are not null 
// in order to make succesfull apend on list
int evalThreadAppend(thread_t *thread, list_t *list) {
    if(NULL == thread) {
        printf("\nThread is null, returning -1\n");
        return -1;
    }
    if(NULL == list) {
        printf("\nList is null, returning -1\n");
        return -1;
    }
    return 1;
}

// add a thread to one of two lists used
// threads and readyQ are used in the createThread function
int appendThread(thread_t *thread, list_t *list) {
    if ( ! evalThreadAppend(thread, list) == 1) {
        return -1;
    }

    node_t *node = list->head;
    node_t *new = malloc(sizeof(node_t));
    new->thread = thread;
    new->next = new->prev = NULL;
    
    if(NULL == node) {
        list->head = new;
    } else {
        while(NULL != node->next) {
            node = node->next;
        }
        node->next = new;
        new->prev = node;
    }

    list->size++;
    
    printf("Success adding thread to list, returning %d\n", thread->status->id);    
    return thread->status->id;
}

// return the number of threads contained in the thread list
unsigned int numNodes(list_t *threads) {
    if(NULL == threads) return 0;
    return threads->size;
}


// initialize temporal list to store threads
void initLists() {
    threads = malloc(sizeof(list_t));    
    threads->head = NULL;
    threads->size = 0;
    srand(time(NULL));
    printf("Lists have been created\n");   
}
