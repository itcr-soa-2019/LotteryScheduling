#include "execution.h"


/**
 * read from keyboard num of threads to create
 */
int readThreadsNum()
{
    int threadsNum;
    printf("\nEnter threads to run: ");
    scanf("%d", &threadsNum);   

    if (MAX_THREADS < threadsNum)
    {
        threadsNum = MAX_THREADS;
    }

    return threadsNum;
}

/**
 * Read from keyboard the thread initial configuration 
 */
struct execution readFromKeyboard(){
    struct execution exInfo;
    printf("Enter Operation Mode: \n [1]: Expropiative [2]: NonExpropiative: ");
    scanf("%d", &exInfo.operationMode);
    exInfo.numThreads = readThreadsNum();
    printf("Enter Amount of tickets per thread: ");
    scanf("%d", &exInfo.tickets);
    printf("Enter Amount of work units per thread: ");
    scanf("%d", &exInfo.workUnits);
    printf("Enter quantum size: ");
    scanf("%d", &exInfo.quantumSize);
    return exInfo;
}

/**
 * Read from file the thread initial configuration
 */
struct execution readFromFile(char *filename)
{
	struct execution exec;
	FILE *file = fopen (filename, "r");

	if (file != NULL)
	{
		char line[MAXBUF];
		int i = 0, value = 0;

		while(fgets(line, sizeof(line), file) != NULL)
		{
			char *cfline;
			cfline = strstr((char *)line, DELIM);
			cfline = cfline + strlen(DELIM);            
            value = atoi(cfline);

			if (i == 0){
                exec.operationMode = value;
			} else if (i == 1){
                exec.numThreads = value;
			} else if (i == 2){
				exec.tickets = value;
			} else if (i == 3){
                exec.workUnits = value;
			} else if (i == 4){
                exec.quantumSize = value;
			}
			i++;
		}
		fclose(file);
	}
	return exec;
}

/**
 * Initial configuration, could be loaded from a
 * configuration file or from the GTK GUI (temp keyboard)
 */
struct execution InitializeExecution(){
    struct execution exInfo;
    
    int mode;    
    printf("Initialize Lottery: \n [1]: Keyboard [2] Config File: ");
    scanf("%d", &mode);
    switch (mode)
    {
        case 1:
            exInfo = readFromKeyboard();
            break;
        case 2:
            exInfo = readFromFile(FILENAME);
            break;    
        default:
            printf("Not a valid execution mode, try again. \n");
            break;
    }

    return exInfo;
}
