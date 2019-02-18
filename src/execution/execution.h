#include <stdio.h>
#include "../threads/thread.h"

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
