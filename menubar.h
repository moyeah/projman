#ifndef __H_MENUBAR__
#define __H_MENUBAR__

int menubar (GtkWidget *main_window, GtkWidget *main_grid);

/* Callback functions */
void on_file_new  (GtkWidget *widget, gpointer data);
void on_file_quit (GtkWidget *widget, gpointer data);

#endif
