#include <gtk/gtk.h>

int
newprojectdialog (GtkWidget *main_window)
{
  GtkWidget *dialog;
  GtkWidget *content_area;
  GtkWidget *project_frame;
  GtkWidget *project_grid;
  GtkWidget *project_name_label;
  GtkWidget *project_name;

  dialog = gtk_dialog_new_with_buttons ("Creating a new Project...",
                                        GTK_WINDOW (main_window),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_STOCK_APPLY,
                                        GTK_RESPONSE_APPLY,
                                        GTK_STOCK_CANCEL,
                                        GTK_RESPONSE_CANCEL,
                                        NULL);

//  gtk_window_set_default (GTK_WINDOW (dialog),

  content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));

  project_frame = gtk_frame_new ("Project:");
  gtk_box_pack_start (GTK_BOX (content_area),
                      project_frame,
                      TRUE,
                      TRUE,
                      0);

  project_grid = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (project_frame),
                     project_grid);

  project_name_label = gtk_label_new_with_mnemonic ("_Name:");
  gtk_grid_attach (GTK_GRID (project_grid),
                   project_name_label,
                   0, 0, 1, 1);

  project_name = gtk_entry_new ();
  gtk_entry_set_activates_default (GTK_ENTRY (project_name), TRUE);
  gtk_label_set_mnemonic_widget (GTK_LABEL (project_name_label),
                                 project_name);
  gtk_grid_attach (GTK_GRID (project_grid),
                   project_name,
                   1, 0, 1, 1);

  gtk_widget_show_all (dialog);

  gint result = gtk_dialog_run (GTK_DIALOG (dialog));

  switch (result)
  {
    case GTK_RESPONSE_APPLY:
      break;
    default:
      break;
  }

  gtk_widget_destroy (dialog);

  return 0;
}
