#include <gtk/gtk.h>

#include "mainwindow.h"
#include "menubar.h"
#include "buttonmenu.h"

int
mainwindow (int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *main_grid;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Project Management");
  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW (window), 800, 600);

  main_grid = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (window), main_grid);

  menubar (main_grid);
  buttonmenu (main_grid);

  g_signal_connect (window, "delete-event",
                    G_CALLBACK (on_delete_event), NULL);
  g_signal_connect (window, "destroy",
                    G_CALLBACK (gtk_main_quit), NULL);

  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}

static gboolean
on_delete_event (GtkWidget *widget,
                 GdkEvent  *event,
                 gpointer   data)
{
  GtkWidget *dialog;
  gboolean   response;

  dialog = gtk_message_dialog_new (GTK_WINDOW (widget),
                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                   GTK_MESSAGE_QUESTION,
                                   GTK_BUTTONS_YES_NO,
                                   "Are you sure you want to quit?");

  gtk_window_set_title (GTK_WINDOW (dialog),
                        "Leaving application?");

  gint result = gtk_dialog_run (GTK_DIALOG (dialog));

  switch (result)
  {
    case GTK_RESPONSE_YES:
      response = FALSE;
      break;
    default:
      response = TRUE;
      break;
  }

  gtk_widget_destroy (dialog);
      
  return response;
}
