#include "../threads/thread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 


#define DELIM "="
#define MAXBUF 1024
#define FILENAME "execution.conf"


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
    int numThreads;
    int tickets;
    int workUnits;
    int quantumSize;
};

struct execution InitializeExecution();