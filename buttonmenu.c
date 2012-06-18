#include <gtk/gtk.h>

#include "buttonmenu.h"

int
buttonmenu (GtkWidget *main_grid)
{
  GtkWidget *grid;
  GtkWidget *button;

  grid = gtk_grid_new ();
  gtk_grid_attach (GTK_GRID (main_grid), grid, 0, 0, 1, 1);

  button = gtk_button_new_with_label ("Create project");
  g_signal_connect (button, "clicked",
                    G_CALLBACK (create_project), NULL);

  gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);

  button = gtk_button_new_with_label ("Edit project");
  g_signal_connect (button, "clicked",
                    G_CALLBACK (edit_project), NULL);

  gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);

  return 0;
}

static void
create_project (GtkWidget *widget,
                gpointer   data)
{
  g_print ("Create project\n");
}

static void
edit_project (GtkWidget *widget,
              gpointer   data)
{
  g_print ("Edit project\n");
}
