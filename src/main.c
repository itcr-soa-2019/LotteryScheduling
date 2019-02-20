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



/**
 * Main execution method
 */
int main(int argc, char **argv)
{        
    initLists();    

    struct execution exeInfo = InitializeExecution();
    int threadsNum = 0;
    threadsNum = exeInfo.numThreads;
	
    for (int i = 0; i < threadsNum; i++)
    {
        createThread(calculateArcTangent);
    }
	
    printf("\nOperationMode: %d\n", exeInfo.operationMode);
	printf("NumThreads: %d\n", exeInfo.numThreads);
	printf("NumTickets: %d\n", exeInfo.tickets);
	printf("WorkUnits: %d\n", exeInfo.workUnits);
	printf("QuantumSize: %d\n", exeInfo.quantumSize);

    return 0;
}