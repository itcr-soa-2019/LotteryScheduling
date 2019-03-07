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
#include "scheduler/scheduler.h"

void stub_reporter(double p){
    printf("Thread progress %f \n", p);
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
    for (int i = 0; i < threadsNum; i++)
    {
        thread_t *thread = malloc(sizeof(thread_t));
        task_t *task = malloc(sizeof(task_t));
        thread-> id = i;
        task->thread = thread;
        task->workUnits = 4;
        piCalculation(task, stub_reporter); //executeTask(task);
    }
    calculated_pi = 0;
    for(int x= 0; x< threadsNum; x++)
    {
        calculated_pi += partialValues[x];
        printf("%f\n",partialValues[x]);
    }
    printf("PI:%f\n", (double)calculated_pi * 4.0);
}

void schedulerTester() {
    //create threads
    thread_t *thread1 = malloc(sizeof(thread_t));
    thread1-> id = 1;
    thread_t *thread2 = malloc(sizeof(thread_t));
    thread2-> id = 2;
    thread_t *thread3 = malloc(sizeof(thread_t));
    thread3-> id = 3;

    //create task
    task_t* test = initTask(1, 3, 3, 1,  1, thread1);
    task_t* test2 = initTask(2, 5, 3, 1,  1, thread2);
    task_t* test3 = initTask(3, 1, 3, 1,  1, thread3);

    //create tasklist
    task_list_t* testList = initTaskList();
    appendTask(test, testList);
    appendTask(test2, testList);
    appendTask(test3, testList);

    // start scheduling
    initScheduler(1, 9, testList);
}


/**
 * Main execution method
 */
int main(int argc, char **argv)
{  
    schedulerTester();
    initLists();    
    piCalcTester();
    printExecution();
    initLotterySchedule(runThread);
    return 0;
}
