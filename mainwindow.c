#include <gtk/gtk.h>

#include "exitdialog.h"
#include "menubar.h"
#include "buttonmenu.h"

static gboolean
on_delete_event (GtkWidget *widget,
                 GdkEvent  *event,
                 gpointer   data)
{
  return exitdialog (widget);
}

static void
on_destroy (GtkWidget *widget,
            gpointer   data)
{
  gtk_main_quit ();
}

int
mainwindow (int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *main_grid;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Project Management");
  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW (window),
                                           gdk_screen_width () * 3/4,
                                           gdk_screen_height () * 3/4);

  main_grid = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (window), main_grid);

  menubar (window, main_grid);
//  buttonmenu (main_grid);

  g_signal_connect (window, "delete-event",
                    G_CALLBACK (on_delete_event), NULL);
  g_signal_connect (window, "destroy",
                    G_CALLBACK (on_destroy), NULL);

  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}
