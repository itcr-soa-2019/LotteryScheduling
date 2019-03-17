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

#include "execution/execution.h"
#include "jobs/piCalc.h"
#include "scheduler/scheduler.h"
#include "ui/ui_functions.h"


static gboolean
update_progress_in_timeout (gpointer pbar)
{
    printf("Thread progress");
    return TRUE;
}

/**
 *  Tester method for Pi calculation
 */
void piCalcTester(){
    struct execution exeInfo = initializeExecution();
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
        // piCalculation(taskm); //executeTask(task);
    }
    calculated_pi = 0;
    for(int x= 0; x< threadsNum; x++)
    {
        calculated_pi += partialValues[x];
        printf("%f\n",partialValues[x]);
    }
    printf("PI:%f\n", (double)calculated_pi * 4.0);
}

void schedulerTesterWorkingExample() {
    //create threads
    thread_t *thread1 = createThread(runThread, 3, 3, 0.3);
    thread_t *thread2 = createThread(runThread, 5, 1, 0.3); 
    thread_t *thread3 = createThread(runThread, 1, 3, 0.3);  

    //create task
    /*el cpuYieldPercentage tiene que ser 1 hasta que correr los threads sirva y el progreso en el 
    piCalc se retome después de un cambio de contexto. porque sino nunca se cumple la condición de task
    completado del allocateNextTask()*/
    task_t* test = initTask(3, 3, 1, 0.3,  0, thread1); 
    task_t* test2 = initTask(5, 6, 1, 0.3, 0, thread2);
    task_t* test3 = initTask(1, 6, 1, 0.3, 0, thread3);

    //create tasklist
    task_list_t* testList = initTaskList(runThread);
    appendTask(test, testList);
    appendTask(test2, testList);
    appendTask(test3, testList);

    // start scheduling
    //initScheduler(1, 9, testList); // expropiative
    //initScheduler(0, 9, testList); //non-expropiative
}

void schedulerTesterFromConfigFile() {
    //initialize config file
    struct execution exeInfo = initializeExecution();   
    hideUnusedThreadsUI(exeInfo.numThreads); 
    partialValues = calloc(sizeof(double),exeInfo.numThreads);
    printExecution();

    //create tasklist, threads and tasks
    task_list_t* tasks = initTaskList(runThread);
    printTaskList(tasks);

    //start scheduling
    int totalTickets = getTotalTickets();
    initScheduler(exeInfo.operationMode, totalTickets, exeInfo.numThreads, tasks); 
}



static gpointer
worker (gpointer data)
{
   schedulerTesterFromConfigFile();
}

// Handler of the Start button clicked event
void start_application() {  
    GThread    *thread;
   // g_timeout_add (100, update_progress_in_timeout, NULL);
    thread = g_thread_new ("worker", worker, NULL);
    g_thread_unref (thread);
    printf("Scheduling Done");
}


// After scheduler start then we need to hide threads that are not
// going to be used
void hideUnusedThreadsUI(long numThreads){
    for(size_t i = numThreads; i < 12; i++)
    { 
        printf("Hide Thread: %ld", i);
        hide_thread(builder, i);
    }  
    while (g_main_context_iteration(NULL, FALSE));
}


int initGtkUI(int argc, char **argv)
{   
    GObject *window;
    GObject *button;
    GError *error = NULL;

    gtk_init (&argc, &argv);

    /* Construct a GtkBuilder instance and load our UI description */
    builder = gtk_builder_new ();
    if (gtk_builder_add_from_file (builder, "builder.ui", &error) == 0)
    {
        g_printerr ("Error loading file: %s\n", error->message);
        g_clear_error (&error);
        return 1;
    }
    
    /* Connect signal handlers to the constructed widgets. */
    window = gtk_builder_get_object (builder, "main_window");
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    button = gtk_builder_get_object (builder, "start_scheduler");
    g_signal_connect (button, "clicked", G_CALLBACK (start_application), NULL);

    button = gtk_builder_get_object (builder, "exit_application");
    g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);
    gtk_main();
}

/**
 * Main execution method
 */
int main(int argc, char **argv)
{   
    //schedulerTesterWorkingExample(); //para que sirva, hay que comentar la creación de threads en initTaskList()
    initGtkUI(argc, argv);
}
