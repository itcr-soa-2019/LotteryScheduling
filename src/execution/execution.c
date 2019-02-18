#include "execution.h"



/**
 * read from keyboard num of threads to create
 */
int readThreadsNum()
{
    int threadsNum;
    printf("\nEnter threads to run:");
    scanf("%d", &threadsNum);   

    if (MAX_THREADS < threadsNum)
    {
        threadsNum = MAX_THREADS;
    }

    return threadsNum;
}

struct execution InitializeExecution(){
    struct execution exInfo;
    printf("Enter Operation Mode: \n [1]: Expropiative [2]: NonExpropiative: \n ");
    scanf("%d", &exInfo.operationMode);
    exInfo.numThreads = readThreadsNum();
    printf("Enter Amount of tickets per thread");
    scanf("%d", &exInfo.tickets);
    printf("Enter Amount of work units per thread");
    scanf("%d", &exInfo.workUnits);
    printf("Enter quantum size");
    scanf("%d", &exInfo.workUnits);
    return exInfo;
}

