#include <gtk/gtk.h>

#include "menubar.h"

int
menubar (GtkWidget *main_grid)
{
  GtkWidget *menubar;
  GtkWidget *filemenu;
  GtkWidget *file;
  GtkWidget *new;
  GtkWidget *open;
  GtkWidget *quit;
  GtkWidget *separator;

  menubar = gtk_menu_bar_new ();
  filemenu = gtk_menu_new ();

  file = gtk_menu_item_new_with_mnemonic ("_File");
  new = gtk_image_menu_item_new_from_stock (GTK_STOCK_NEW, NULL);
  open = gtk_image_menu_item_new_from_stock (GTK_STOCK_OPEN, NULL);
  quit = gtk_image_menu_item_new_from_stock (GTK_STOCK_QUIT, NULL);

  separator = gtk_separator_menu_item_new ();

  gtk_menu_item_set_submenu (GTK_MENU_ITEM (file), filemenu);
  gtk_menu_shell_append (GTK_MENU_SHELL (filemenu), new);
  gtk_menu_shell_append (GTK_MENU_SHELL (filemenu), open);
  gtk_menu_shell_append (GTK_MENU_SHELL (filemenu), separator);
  gtk_menu_shell_append (GTK_MENU_SHELL (filemenu), quit);
  gtk_menu_shell_append (GTK_MENU_SHELL (menubar), file);

  gtk_grid_attach (GTK_GRID (main_grid), menubar, 0, 0, 1, 1);

  g_signal_connect (G_OBJECT (quit), "activate",
                    G_CALLBACK (on_quit), NULL);

  return 0;
}

void
on_quit ()
