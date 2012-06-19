#ifndef __H_MENUBAR__
#define __H_MENUBAR__

int menubar (GtkWidget *window, GtkWidget *main_grid);

/* Callback functions */
void on_quit (GtkWidget *widget, GdkEvent *event, GtkWidget *data);

#endif
