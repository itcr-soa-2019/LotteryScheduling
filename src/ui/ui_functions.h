#include <gtk/gtk.h>
#include "../scheduler/task.h"

void hide_thread(GtkBuilder *builder, int index);

void update_thread(GtkBuilder *builder, task_t *task);

void update_pi_value(GtkBuilder *builder, double piValue);
