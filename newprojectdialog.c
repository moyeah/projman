#include <gtk/gtk.h>

enum
{
  REFERENCE,
  DESCRIPTION,
  AMOUNT,
  N_COLUMNS
};

void
set_column (GtkTreeViewColumn *column)
{
  gtk_tree_view_column_set_spacing (column, 5);
  gtk_tree_view_column_set_resizable (column, TRUE);
  gtk_tree_view_column_set_expand (column, TRUE);
  gtk_tree_view_column_set_alignment (column, 0.5);
  gtk_tree_view_column_set_reorderable (column, TRUE);
}

int
newprojectdialog (GtkWidget *main_window)
{
  GtkWidget *dialog;
  GtkWidget *content_area;
  GtkWidget *label;
  GtkWidget *frame;
  GtkWidget *grid;
  GtkWidget *name;
  GtkWidget *scrollable_window;
  GtkWidget *view;
  GtkTextBuffer *description;
  GtkTreeStore *orders;
  GtkWidget *tree;
  GtkTreeViewColumn *column;
  GtkCellRenderer *renderer;
  GtkTreeIter root_iter;
  GtkTreeIter child_iter;

  dialog = gtk_dialog_new_with_buttons ("Creating a new Project...",
                                        GTK_WINDOW (main_window),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_STOCK_ADD,
                                        GTK_RESPONSE_APPLY,
                                        GTK_STOCK_CANCEL,
                                        GTK_RESPONSE_CANCEL,
                                        NULL);

//  gtk_window_set_default (GTK_WINDOW (dialog),

  content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
  gtk_window_set_default_size (GTK_WINDOW (dialog),
                               gdk_screen_width () * 1/2,
                               gdk_screen_height () * 1/2);
  gtk_container_set_border_width (GTK_CONTAINER (content_area), 10);

  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label),
                        "<b>Project</b>");

  frame = gtk_frame_new (NULL);
  gtk_frame_set_label_widget (GTK_FRAME (frame),
                              label);
  gtk_box_pack_start (GTK_BOX (content_area),
                      frame,
                      TRUE,
                      TRUE,
                      0);

  grid = gtk_grid_new ();
  gtk_grid_set_column_spacing (GTK_GRID (grid), 10);
  gtk_grid_set_row_spacing (GTK_GRID (grid), 10);
  gtk_container_set_border_width (GTK_CONTAINER (grid), 10);
  gtk_container_add (GTK_CONTAINER (frame), grid);

  label = gtk_label_new_with_mnemonic ("_Name");
  gtk_widget_set_halign (label, GTK_ALIGN_END);
  gtk_grid_attach_next_to (GTK_GRID (grid),
                           label,
                           NULL,
                           GTK_POS_TOP,
                           1, 1);

  name = gtk_entry_new ();
  gtk_entry_set_activates_default (GTK_ENTRY (name), TRUE);
  gtk_label_set_mnemonic_widget (GTK_LABEL (label), name);
  gtk_widget_set_hexpand (name, TRUE);
  gtk_grid_attach_next_to (GTK_GRID (grid),
                           name,
                           label,
                           GTK_POS_RIGHT,
                           1, 1);

  label = gtk_label_new_with_mnemonic ("_Description");
  gtk_widget_set_halign (label, GTK_ALIGN_END);
  gtk_widget_set_valign (label, GTK_ALIGN_START);
  gtk_grid_attach_next_to (GTK_GRID (grid),
                           label,
                           NULL,
                           GTK_POS_BOTTOM,
                           1, 1);

  scrollable_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_set_hexpand (scrollable_window, TRUE);
  gtk_widget_set_vexpand (scrollable_window, TRUE);
  gtk_grid_attach_next_to (GTK_GRID (grid),
                           scrollable_window,
                           label,
                           GTK_POS_RIGHT,
                           1, 1);

  view = gtk_text_view_new ();
  gtk_label_set_mnemonic_widget (GTK_LABEL (label), view);
  gtk_widget_set_hexpand (view, TRUE);
  gtk_container_add (GTK_CONTAINER (scrollable_window), view);

  description = gtk_text_view_get_buffer (
                          GTK_TEXT_VIEW (view));

  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label), "<b>Orders and Payments</b>");

  frame = gtk_frame_new (NULL);
  gtk_frame_set_label_widget (GTK_FRAME (frame), label);
  gtk_box_pack_start (GTK_BOX (content_area),
                      frame,
                      TRUE,
                      TRUE,
                      0);

  orders = gtk_tree_store_new (N_COLUMNS,
                               G_TYPE_STRING,
                               G_TYPE_STRING,
                               G_TYPE_DOUBLE);
  gtk_tree_store_append (orders, &root_iter, NULL);
  gtk_tree_store_append (orders, &child_iter, &root_iter);

  tree = gtk_tree_view_new_with_model (GTK_TREE_MODEL (orders));

  renderer = gtk_cell_renderer_text_new ();
  g_object_set (G_OBJECT (renderer), "editable", TRUE, NULL);
  column = gtk_tree_view_column_new_with_attributes ("Reference",
                                                     renderer,
                                                     "text",
                                                     REFERENCE,
                                                     NULL);
  set_column (column);
  gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);

  renderer = gtk_cell_renderer_text_new ();
  g_object_set (G_OBJECT (renderer), "editable", TRUE, NULL);
  column = gtk_tree_view_column_new_with_attributes ("Description",
                                                     renderer,
                                                     "text",
                                                     DESCRIPTION,
                                                     NULL);
  set_column (column);
  gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);

  renderer = gtk_cell_renderer_text_new ();
  g_object_set (G_OBJECT (renderer), "editable", TRUE, NULL);
  column = gtk_tree_view_column_new_with_attributes ("Amount",
                                                     renderer,
                                                     "text",
                                                     AMOUNT,
                                                     NULL);
  set_column (column);
  gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);

  gtk_container_add (GTK_CONTAINER (frame), tree);

  gtk_widget_show_all (dialog);

  gint result = gtk_dialog_run (GTK_DIALOG (dialog));

  switch (result)
  {
    case GTK_RESPONSE_OK:
      break;
    default:
      break;
  }

  gtk_widget_destroy (dialog);

  return 0;
}
