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
#include "execution/execution.h"
#include "jobs/piCalc.h"

/**
 * Main execution method
 */
int main(int argc, char **argv)
{        
    initLists();    

    struct execution exeInfo = InitializeExecution();
    int threadsNum = 0;
    threadsNum = exeInfo.numThreads;
    numThreads = threadsNum;
    partialValues = calloc(sizeof(double),numThreads);
    for (int i = 0; i < threadsNum; i++)
    {
        thread_t *thread = malloc(sizeof(thread_t));
        thread-> id = i;
        printf("\n");
        // createThread(calculateArcTangent);
        piCalculation(thread);
    }
    calculated_pi = 0;
    for(int x= 0; x< threadsNum; x++)
    {
        calculated_pi += partialValues[x];
        printf("%f\n",partialValues[x]);
    }
    printf("PI:%f\n", (double)calculated_pi * 4.0);
    
    printf("\nOperationMode: %d\n", exeInfo.operationMode);
	printf("NumThreads: %d\n", exeInfo.numThreads);
	printf("NumTickets: %d\n", exeInfo.tickets);
	printf("WorkUnits: %d\n", exeInfo.workUnits);
	printf("QuantumSize: %d\n", exeInfo.quantumSize);
	
    return 0;
}