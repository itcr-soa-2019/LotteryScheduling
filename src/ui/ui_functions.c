#include "ui_functions.h"

// Hide a thread info section
void hide_thread(GtkBuilder *builder, int index){
  GObject *grid;
  char* name = (char*) malloc(sizeof(char)*6);
  sprintf(name, "grid%d", index);
  grid = gtk_builder_get_object(builder, name);
  gtk_widget_set_visible(GTK_WIDGET(grid), 0); //Make it visible
}

// Update the ui widget according to a task 
void update_thread(GtkBuilder *builder, int id, int state, double progressVal) {
  GObject *status;
  GObject *progress;
  //status_value0
  char* status_name = (char*) malloc(sizeof(char)*50);
  char* statusValue = (char*) malloc(sizeof(char)*50);
  sprintf(status_name, "status_value%d", id);
  printf("Updating Label: %s", status_name);
  status = gtk_builder_get_object(builder, status_name);
  // Just to get a string value from the status number
  switch (state)
  {
    case 1:
      statusValue = "Running";
      break;
    case 4:
      statusValue = "Done";
      break;
    default:
      statusValue = "Idle";
      break;
  }
  gtk_label_set_text(GTK_LABEL(status), statusValue);
  //progress_1
  char* progress_name = (char*) malloc(sizeof(char)*11);
  sprintf(progress_name, "progress_%d", id);
  progress = gtk_builder_get_object(builder, progress_name);
  printf("Updating Progress: %s", progress_name);
  gtk_widget_set_visible(GTK_WIDGET(progress), 1); //Make it visible
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress), progressVal);
  while(gtk_events_pending())
	gtk_main_iteration();
}

void update_pi_value(GtkBuilder *builder, double piValue) {
  printf("Updating Label: %f", piValue);
  GObject *piLabel;
  char calculatedPI[200];
  sprintf(calculatedPI, "%2.13f", piValue);
  printf("TOTAL: %s",calculatedPI);
  piLabel = gtk_builder_get_object(builder, "label_pi_value");
  gtk_label_set_text (GTK_LABEL(piLabel), calculatedPI);
  // while(gtk_events_pending())
	// gtk_main_iteration();
}