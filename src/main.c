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





task_t *task1;
task_t *task2;

void reportProgress2(double p) {
    if(currentTask->thread->id >= 1){
        saveThread(task2->thread);
        printf("FINISH JOB");
        return;
    }
    if(p == 1.0){
        printf("Thread DONE");
        saveThread(task1->thread);
        currentTask = task2;
        Resume_Thread(task2->thread);        // Start Second
    } else {
        printf("Thread Continue");
    }
}
void stub_reporter(){
     while(1){
        piCalculation(currentTask, reportProgress2);
        printf("TESTTTTTT");
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
    // for (int i = 0; i < threadsNum; i++)
    // {
    thread = createThread(stub_reporter,10,5,10);
    task1 = malloc(sizeof(task_t));
    thread-> id = 0;
    task1->thread = thread;
    task1->workUnits = 4;
    currentTask = task1;

    thread = createThread(stub_reporter,10,5,10);
    task2 = malloc(sizeof(task_t));
    thread-> id = 1;
    task2->thread = thread;
    task2->workUnits = 4;
    // piCalculation(task, stub_reporter);
    //if(saveThread(task->thread) == 0){
    printf("TEST");
    Resume_Thread(task1->thread); // Start first

       // }
        // delay(1000);
    // }
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