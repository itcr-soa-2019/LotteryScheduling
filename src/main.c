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
#include "ui/ui_functions.h"

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
        piCalculation(task, stub_reporter);
    }
    calculated_pi = 0;
    for(int x= 0; x< threadsNum; x++)
    {
        calculated_pi += partialValues[x];
        printf("%f\n",partialValues[x]);
    }
    printf("PI:%f\n", (double)calculated_pi * 4.0);
}

// Handler of the Start button clicked event
void start_application() {
    initLists();    
    piCalcTester();
    printExecution();
    initLotterySchedule(runThread);
}

/**
 * Main execution method
 */
int main(int argc, char **argv)
{   
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
  window = gtk_builder_get_object (builder, "main_window");
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  button = gtk_builder_get_object (builder, "start_scheduler");
  g_signal_connect (button, "clicked", G_CALLBACK (start_application), NULL);

//   button = gtk_builder_get_object (builder, "button2");
//   g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

  button = gtk_builder_get_object (builder, "exit_application");
  g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);
  GObject *progress2;
  progress2 = gtk_builder_get_object(builder, "progress_2");
  gtk_widget_set_visible(GTK_WIDGET(progress2), 1); //Make it visible
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress2), 0.50);
 // Sample hide some of the threads
  for(size_t i = 6; i < 12; i++)
  {
    hide_thread(builder, i);
  }
  

  gtk_main ();
}