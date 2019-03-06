/* 
   ____    ____     ___           ___    ____    ___   ____
  / ___/  / __ \   /   |         |__ \  / __ \  <  /  / __ \
  \__ \  / / / /  / /| |         __/ / / / / /  / /  / /_/ /
 ___/ / / /_/ /  / ___ |        / __/ / /_/ /  / /   \__, /
/____/  \____/  /_/  |_|       /____/ \____/  /_/   /____/

Instituto Tecnológico de Costa Rica
Maestría en Computación
Sistemas Operativos Avanzados
Prof: Francisco Torres Rojas, PHD.
Integrantes: Fabiola Espinoza
			 Nathalia Gonzalez
			 Manuel Figueroa
			 José Somarribas
			 Esteban Leandro
Proyecto 1: Lottery Scheduling */

 
#include "jobs/jobs.h"
#include "lottery/lottery.h"
#include "jobs/piCalc.h"
#include <stdio.h>
#include <stdlib.h>


void stub_reporter(){
     while(1){
        piCalculation(currentTask, reportProgress);
        printf("TESTTTTTT");
        saveThread(currentTask->thread);
        break;
     }
}

/**
 *  Tester method for Pi calculation
 */
void piCalcTester(){
    struct execution exeInfo = InitializeExecution();
    int threadsNum = 0;
    threadsNum = exeInfo.numThreads;
    numThreads = threadsNum;
    partialValues = calloc(sizeof(double),numThreads);
    thread_t *thread;
    for (int i = 0; i < threadsNum; i++)
    {
        thread = createThread(stub_reporter,10,5,10);
        task_t *task = malloc(sizeof(task_t));
        thread-> id = i;
        task->thread = thread;
        task->workUnits = 4;
        currentTask = task;
       // piCalculation(task, stub_reporter);
        //if(saveThread(task->thread) == 0){
            printf("TEST");
            Resume_Thread(task->thread);

       // }
        // delay(1000);
    }
    // Resume_Thread(thread);
    calculated_pi = 0;
    for(int x= 0; x< threadsNum; x++)
    {
        calculated_pi += partialValues[x];
        printf("%f\n",partialValues[x]);
    }
    printf("PI:%f\n", (double)calculated_pi * 4.0);
}

/**
 * Main execution method
 */
int main(int argc, char **argv)
{   
    initLists();    
    piCalcTester();
    // printExecution();
    // initLotterySchedule(runThread);
    return 0;
}