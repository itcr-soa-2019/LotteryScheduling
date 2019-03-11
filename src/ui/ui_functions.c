#include "ui_functions.h"

// Hide a thread info section
void hide_thread(GtkBuilder *builder, int index){
  GObject *grid;
  char* name = (char*) malloc(sizeof(char)*6);
  sprintf(name, "grid%d", index);
  grid = gtk_builder_get_object(builder, name);
  gtk_widget_set_visible(GTK_WIDGET(grid), 0); //Make it visible
}