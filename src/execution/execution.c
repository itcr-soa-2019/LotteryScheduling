#include "execution.h"

// file settings configuration
const char *OPERATION_MODE = "operationMode";
const char *NUMBER_THREADS = "numThreads";
const char *TICKETS_THREAD = "tickets";
const char *WORK_THREAD = "workUnits";
const char *QUANTUM_SIZE = "quantumSize";
const char *YIELD_CPU = "cpuYieldPercentage";

// randomize tickets and work units
time_t timer; 


/**
 * read from keyboard num of threads to create
 */
int readThreadsNum() {
    int threadsNum;
    printf("Enter threads to run: ");
    scanf("%d", &threadsNum);
    if (MAX_THREADS < threadsNum) {
        threadsNum = MAX_THREADS;
    }
    return threadsNum;
}

/**
 * Read from keyboard the thread initial configuration 
 */
struct execution readFromKeyboard(){
    int i;        
    srand((unsigned) time(&timer));
    
    printf("Enter Operation Mode: \n[1] Expropiative [2] NonExpropiative: ");
    scanf("%d", &executor.operationMode);
    executor.numThreads = readThreadsNum();
    executor.tickets = (long*) malloc(executor.numThreads * sizeof(long));
    executor.workUnits = (long*) malloc(executor.numThreads * sizeof(long));
    
    printf("Tickets will be assigned randomly\n");
    for(i = 0; i < executor.numThreads; i++) 
    {
        executor.tickets[i] = rand() % MAX_TICKETS;
    }
    printf("Work units will be assigned randomly\n");
    for(i = 0; i < executor.numThreads; i++) 
    {
        executor.workUnits[i] = rand() % MAX_WORK_UNITS;
    }
    
    printf("Enter quantum size: \n");
    scanf("%d", &executor.quantumSize);    
    return executor;
}

/**
 * Read from configuration file
 */
struct execution readFromFile(char *filename) {	
	FILE *file = fopen (filename, "r");
	if (file != NULL) {
		char line[MAXBUF];
		while(fgets(line, sizeof(line), file) != NULL) {
            char *attLine = strtok(line, DELIM);
            char *valLine = strtok(NULL, DELIM);
            if (strcmp(attLine, OPERATION_MODE) == 0) {
                executor.operationMode = atoi(valLine);
            } else if (strcmp(attLine, NUMBER_THREADS) == 0) {
                executor.numThreads = atoi(valLine);
                executor.tickets = (long*) malloc(executor.numThreads * sizeof(long));
                executor.workUnits = (long*) malloc(executor.numThreads * sizeof(long));
            } else if (strcmp(attLine, TICKETS_THREAD) == 0) {
                char *t_tickets = strtok(valLine, DELIM_LIST);
                int i = 0;
                while(t_tickets != NULL && i < executor.numThreads)
                {
                    executor.tickets[i] = strtol(t_tickets, (char **)NULL, 10);
                    t_tickets = strtok(NULL, DELIM_LIST);
                    i++;
                }
            } else if (strcmp(attLine, WORK_THREAD) == 0) {
                char *t_workUnits = strtok(valLine, DELIM_LIST);
                int i = 0;
                while(t_workUnits != NULL && i < executor.numThreads)
                {
                    executor.workUnits[i] = strtol(t_workUnits, (char **)NULL, 10);
                    t_workUnits = strtok(NULL, DELIM_LIST);
                    i++;
                }
            } else if (strcmp(attLine, QUANTUM_SIZE) == 0) {
                executor.quantumSize = atoi(valLine);
            } else if (strcmp(attLine, YIELD_CPU) == 0) {                
                executor.cpuYieldPercentage = strtod(valLine, NULL);
            } else {                
                printf("Invalid execution setting: %s with line %s\n", attLine, line);
            }
		}
		fclose(file);
	}
	return executor;
}

/**
 * Print the execution struct
 */
void printExecution() {
    int i = 0;
    printf("\n***************** EXECUTOR *****************\n");
    printf("Operation Mode: %d\n", executor.operationMode);
	printf("THREADS: %ld\n", executor.numThreads);
    printf("TICKETS: ");    
    for(i = 0; i < executor.numThreads-1; i++)
    {
        printf("%ld, ", executor.tickets[i]);
    }
    printf("%ld. ", executor.tickets[i]);
    printf("\nWORK: ");
    for(i = 0; i < executor.numThreads-1; i++)
    {
        printf("%ld, ", executor.workUnits[i]);
    }
    printf("%ld. ", executor.workUnits[i]);
	printf("\nQuantum Size: %d\n", executor.quantumSize);
    printf("CPU Percentage: %lf\n", executor.cpuYieldPercentage);
}

/**
 *  return the total tickets among the threads
 */
int getTotalTickets(){
    int total = 0, i = 0;
    for(i = 0; i < executor.numThreads; i++)
    {
        total += executor.tickets[i];
    }
    return total;
}

/**
 * Initial configuration, could be used for development mode
 * to test reading from keyboard or file
 */
struct execution testInitializeExecution(){
    int mode;
    printf("Initialize Lottery: \n[1] Keyboard [2] Config File: ");
    scanf("%d", &mode);
    switch (mode)
    {
        case 1:
            executor = readFromKeyboard();
            break;
        case 2:
            executor = readFromFile(FILENAME);
            break;
        default:
            printf("Not a valid execution mode, try again. \n");
            break;
    }
    return executor;
}

/**
 * Initial configuration, would be loaded 
 * from the GTK GUI
 */
struct execution initializeExecution(){    
    executor = readFromFile(FILENAME);
    return executor;
}
