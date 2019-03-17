#include <gtk/gtk.h>
#include "../scheduler/task.h"

void hide_thread(GtkBuilder *builder, int index);

void update_thread(GtkBuilder *builder, int id, int state, double progressVal);

void update_pi_value(GtkBuilder *builder, double piValue);
