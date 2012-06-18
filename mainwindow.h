#ifndef __H_MAINWINDOW__
#define __H_MAINWINDOW__

int mainwindow (int argc, char *argv[]);

/* Callback functions */
static gboolean on_delete_event (GtkWidget *widget,
                                 GdkEvent  *event,
                                 gpointer   data);

#endif
