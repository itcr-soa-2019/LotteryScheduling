#include "../threads/thread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>

#define DELIM "="
#define DELIM_LIST ","
#define MAXBUF 1024
#define FILENAME "execution.conf"

struct execution executor;

/**
 * The expected operation modes:
 * Expropiative Mode = 1
 * NonExpropiative Mode = 0
 */
enum OperationMode {
    Expropiative = 1,
    NonExpropiative = 0
};

struct execution
{
    int operationMode;
    long numThreads;
    long* tickets;
    long* workUnits;
    unsigned int quantumSize;
    double cpuYieldPercentage;
};

void printExecution();
struct execution InitializeExecution();
