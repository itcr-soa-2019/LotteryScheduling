
#include "thread.h"

// 64 bit Intel arch
#define JB_SP 6
#define JB_PC 7

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
thread_t* createThread(void *function, long tickets, long workUnits, long cpuYield) {
    thread_t *thread = malloc(sizeof(thread_t));
    thread->status = malloc(sizeof(state_t));
    thread->stack = malloc(STACK_SIZE);
    address_t sp, pc;

    newId++;
    thread->id = newId;
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
    
    return thread;
}

// Saves the thread execution context
int saveThread(thread_t* thread) {
    return sigsetjmp(thread->jmpbuf, 1);
}

// Resumes thread
void Resume_Thread(thread_t* thread) {
    siglongjmp(thread->jmpbuf, 1);
}
