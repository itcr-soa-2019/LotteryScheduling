
#include <malloc.h>
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <math.h>

#ifndef thread_h
#define thread_h

#define MAX_THREADS 5
#define STACK_SIZE 4096
#define TIME_QUANTUM 1 

typedef enum 
{
   READY, 
   RUNNING, 
   YIELDED, 
   YIELDTOSLEEP, 
   YIELDTOSUSPEND, 
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

#ifdef __x86_64__
typedef unsigned long address_t;
#else
typedef unsigned int address_t;
#endif

typedef struct thread_t
{
   char *stack;
   address_t sp;
   address_t pc;
   state_t *status;
   sigjmp_buf jmpbuf;
} thread_t;

typedef struct node_t
{
   thread_t *thread;
   struct node_t *next;
   struct node_t *prev;
} node_t;

typedef struct list_t
{
   node_t *head;
   unsigned int size;
} list_t;


// Creates a new thread with f() being its entry point. 
// The function returns the created thread id (>= 0) or ‐1 to indicate failure.
int createThread(void (*f) (void));

unsigned int numNodes(list_t *threads);

// Function to calculate PI arc tangent
void calculateArcTangent();


// close declarations
#endif