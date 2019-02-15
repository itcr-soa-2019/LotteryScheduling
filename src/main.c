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
#include "threads/thread.h"


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

/**
 * Main execution method
 */
int main(int argc, char **argv)
{
    initLists();

    int threadsNum = 0;
    threadsNum = readThreadsNum();

    for (int i = 0; i < threadsNum; i++)
    {
        printf("\n");
        createThread(calculateArcTangent);
    }
    
    return 0;
}