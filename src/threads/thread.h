#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <time.h>

// header definition
#ifndef thread_h
#define thread_h

// constants definitions
#define STACK_SIZE 4096
#define MAX_THREADS 10
#define MAX_TICKETS 5
#define MAX_WORK_UNITS 50

// structs and enums declarations
typedef unsigned long address_t;

typedef enum 
{
   READY, 
   RUNNING, 
   SUSPENDED, 
   SLEEPING, 
   FINISHED
} threadState_t;

typedef struct state_t
{
   threadState_t threadState;
   int priority;
   unsigned int id;
   unsigned int num_runs;
   unsigned int total_exec_time;
   unsigned int total_sleep_time;
   unsigned int total_wait_time;
   unsigned int avr_exec_time;
   unsigned int avr_wait_time;
   int awake_after; //the time when the thread should awake
} state_t;

typedef struct thread_t
{
   int id;
   char *stack;
   state_t *status;
   long tickets;
   long workUnits;
   double cpuYieldPercentage;
   sigjmp_buf jmpbuf;
} thread_t;


// Creates a new thread with f() being its entry point. 
// The function returns the created thread id (>= 0) or ‐1 to indicate failure.
thread_t* createThread(void *function, long tickets, long workUnits, long cpuYield);

// Saves the thread execution context
int saveThread(thread_t* thread);

// Resumes thread
void Resume_Thread(thread_t* thread);

#endif