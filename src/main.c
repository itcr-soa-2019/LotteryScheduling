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

#include <gtk/gtk.h>
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
    // initLists();    
    // piCalcTester();
    // printExecution();
    // initLotterySchedule(runThread);
    GtkBuilder *builder;
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
  window = gtk_builder_get_object (builder, "window");
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

//   button = gtk_builder_get_object (builder, "button1");
//   g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

//   button = gtk_builder_get_object (builder, "button2");
//   g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

  button = gtk_builder_get_object (builder, "quit");
  g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);
  GObject *progress2;
  progress2 = gtk_builder_get_object(builder, "progress_2");
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress2), 0.50);

  gtk_main ();
}
