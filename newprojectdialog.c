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
  GtkWidget *project_description_label;
  GtkWidget *project_description_view;
  GtkTextBuffer *project_description;

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
  gtk_window_set_default_size (GTK_WINDOW (dialog), 800, 600);
  gtk_container_set_border_width (GTK_CONTAINER (content_area), 10);

  project_frame = gtk_frame_new ("Project");
  gtk_box_pack_start (GTK_BOX (content_area),
                      project_frame,
                      TRUE,
                      TRUE,
                      0);

  project_grid = gtk_grid_new ();
  gtk_grid_set_column_spacing (GTK_GRID (project_grid), 5);
  gtk_container_set_border_width (GTK_CONTAINER (project_grid), 10);
  gtk_container_add (GTK_CONTAINER (project_frame),
                     project_grid);

  project_name_label = gtk_label_new_with_mnemonic ("_Name");
  gtk_grid_attach (GTK_GRID (project_grid),
                   project_name_label,
                   0, 0, 1, 1);

  project_name = gtk_entry_new ();
  gtk_entry_set_activates_default (GTK_ENTRY (project_name), TRUE);
  gtk_label_set_mnemonic_widget (GTK_LABEL (project_name_label),
                                 project_name);
  gtk_widget_set_hexpand (project_name, TRUE);
  gtk_grid_attach (GTK_GRID (project_grid),
                   project_name,
                   1, 0, 1, 1);

  project_description_label = gtk_label_new_with_mnemonic ("_Description");
  gtk_grid_attach (GTK_GRID (project_grid),
                   project_description_label,
                   0, 1, 1, 1);

  project_description_view = gtk_text_view_new ();
  gtk_label_set_mnemonic_widget (GTK_LABEL (project_description_label),
                                 project_description_view);
  gtk_widget_set_hexpand (project_description_view, TRUE);
  gtk_grid_attach (GTK_GRID (project_grid),
                   project_description_view,
                   1, 1, 1, 1);

  project_description = gtk_text_view_get_buffer (
                          GTK_TEXT_VIEW (project_description_view));
  

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
