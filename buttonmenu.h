#ifndef __H_BUTTONMENU__
#define __H_BUTTONMENU__

int buttonmenu (GtkWidget *main_grid);

/* Callback functions */
static void create_project (GtkWidget *widget,
                            gpointer   data);
static void edit_project   (GtkWidget *widget,
                            gpointer   data);

#endif
