#ifndef task_h
#define task_h

typedef struct task_t
{
   int tickets;
   int workUnits;
   int quantumSize; // millisecs if expropiative mode or work % if nonexpropiative mode
   double progress; // Indicates the current progress value of this task
   thread_t *thread;
} task_t;

typedef struct task_node_t
{
   task_t *task;
   struct task_node_t *next;
   struct task_node_t *prev;
} task_node_t;

typedef struct task_list_t
{
   task_node_t *head;
   unsigned int size;
} task_list_t;

// initialize task element
void initTask(int tickets, int workUnits, int quantumSize, thread_t *thread);

// add new element to the tasks list
void appendTask(task_t *task, task_list_t *list);

#endif
