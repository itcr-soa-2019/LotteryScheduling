
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <time.h>
#include <math.h>


// header definition
#ifndef thread_h
#define thread_h

// constants definitions
#define STACK_SIZE 4096
#define MAX_THREADS 10


// structs and enums declarations
typedef unsigned long address_t;

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
int createThread(void (*function) (void));

// add a specific thread to the thread list
int appendThread(thread_t *thread, list_t *list);

// number of nodes
unsigned int numNodes(list_t *threads);

// check memory allocation
void mallocCheck(void *pointer, int lineNumber);

// initialize lists
void initLists();


#endif