#include <gtk/gtk.h>

#include "newprojectgda.h"

static void
on_cell_edited (GtkCellRendererText *renderer,
                gchar               *path_string,
                gchar               *new_text,
                gpointer             model)
{
  GtkTreeIter row;
  GtkTreeIter top;
  guint column_number;
  gboolean is_on_top;

  gtk_tree_model_get_iter_from_string (model, &row, path_string);
  column_number = GPOINTER_TO_UINT (g_object_get_data (G_OBJECT (renderer),
                                    "column"));
  gtk_tree_store_set (model, &row, column_number, new_text, -1);

  is_on_top = gtk_tree_model_iter_previous (model, &row);
  if (is_on_top)
  {
    g_print ("is_on_top\n");
    //gtk_tree_store_remove (model, &row);
  }
  else
    g_print ("NOT\n");
}

static GtkWidget *
frame_new (GtkWidget *content_area, const char *str)
{
  GtkWidget *label;
  GtkWidget *frame;
  GtkWidget *grid;

  label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (label),
                        g_markup_printf_escaped ("<b>%s</b>", str));

  frame = gtk_frame_new (NULL);
  gtk_frame_set_label_widget (GTK_FRAME (frame), label);
  gtk_box_pack_start (GTK_BOX (content_area),
                      frame,
                      FALSE,
                      TRUE,
                      5);

  grid = gtk_grid_new ();
  gtk_grid_set_column_spacing (GTK_GRID (grid), 10);
  gtk_grid_set_row_spacing (GTK_GRID (grid), 10);
  gtk_container_set_border_width (GTK_CONTAINER (grid), 10);
  gtk_container_add (GTK_CONTAINER (frame), grid);

  return grid;
}

static GtkWidget *
entry_new (GtkWidget *grid, const gchar *str)
{
  GtkWidget *label;
  GtkWidget *entry;

  label = gtk_label_new_with_mnemonic (str);
  gtk_widget_set_halign (label, GTK_ALIGN_END);
  gtk_grid_attach_next_to (GTK_GRID (grid),
                           label,
                           NULL,
                           GTK_POS_BOTTOM,
                           1, 1);

  entry = gtk_entry_new ();
  gtk_entry_set_activates_default (GTK_ENTRY (entry), TRUE);
  gtk_label_set_mnemonic_widget (GTK_LABEL (label), entry);
  gtk_widget_set_hexpand (entry, TRUE);
  gtk_grid_attach_next_to (GTK_GRID (grid),
                           entry,
                           label,
                           GTK_POS_RIGHT,
                           1, 1);

  return entry;
}

static GtkTextBuffer *
ml_entry_new (GtkWidget *grid, const gchar *str)
{
  GtkWidget *label;
  GtkWidget *scrollable_window;
  GtkWidget *view;
  GtkTextBuffer *description;

  label = gtk_label_new_with_mnemonic (str);
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

  description = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

  return description;
}

static GtkWidget *
reference_new (GtkWidget *grid)
{

enum
{
  REFERENCE,
  DESCRIPTION,
  AMOUNT,
  N_COLUMNS
};

void
add_column (GtkWidget *tree, const gchar *header, guint e_column)
{
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;

  renderer = gtk_cell_renderer_text_new ();
  g_object_set (G_OBJECT (renderer), "editable", TRUE, NULL);
  g_object_set_data (G_OBJECT (renderer), "column", GUINT_TO_POINTER (e_column));
  g_signal_connect (renderer, "edited", G_CALLBACK (on_cell_edited),
                    gtk_tree_view_get_model (GTK_TREE_VIEW(tree)));
  column = gtk_tree_view_column_new_with_attributes (header,
                                                     renderer,
                                                     "text",
                                                     e_column,
                                                     NULL);
  gtk_tree_view_column_set_spacing (column, 5);
  gtk_tree_view_column_set_resizable (column, TRUE);
  gtk_tree_view_column_set_expand (column, TRUE);
  gtk_tree_view_column_set_alignment (column, 0.5);
  gtk_tree_view_column_set_reorderable (column, TRUE);
  gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);
}

  GtkTreeStore *store;
  GtkTreeIter root_iter;
  GtkTreeIter item_iter;
  GtkWidget *tree;

  store = gtk_tree_store_new (N_COLUMNS,
                              G_TYPE_STRING,
                              G_TYPE_STRING,
                              G_TYPE_STRING); /* Should be G_TYPE_DOUBLE */
  gtk_tree_store_append (store, &root_iter, NULL);
  gtk_tree_store_append (store, &item_iter, &root_iter);

  tree = gtk_tree_view_new_with_model (GTK_TREE_MODEL (store));
  gtk_widget_set_hexpand (tree, TRUE);
  gtk_widget_set_vexpand (tree, TRUE);
  g_object_unref (store);

  add_column (tree, "Reference", REFERENCE);
  add_column (tree, "Description", DESCRIPTION);
  add_column (tree, "Amount", AMOUNT);

  gtk_grid_attach_next_to (GTK_GRID (grid),
                           tree,
                           NULL,
                           GTK_POS_BOTTOM,
                           1, 1);

  return tree;
}

int
newprojectdialog (GtkWidget *main_window)
{
  GtkWidget *dialog;
  GtkWidget *content_area;
  GtkWidget *grid;
  GtkWidget *name;
  GtkTextBuffer *description;
  GtkWidget *customer;
  GtkWidget *orders;
  GtkWidget *internal;
  ProjectInfo *project_info;

  dialog = gtk_dialog_new_with_buttons ("Creating a new Project...",
                                        GTK_WINDOW (main_window),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_STOCK_ADD,
                                        GTK_RESPONSE_APPLY,
                                        GTK_STOCK_CANCEL,
                                        GTK_RESPONSE_CANCEL,
                                        NULL);
  gtk_dialog_set_default_response (GTK_DIALOG (dialog),
                                   GTK_RESPONSE_APPLY);

  gtk_window_set_default_size (GTK_WINDOW (dialog),
                               gdk_screen_width () * 1/2,
                               gdk_screen_height () * 1/2);

  content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
  gtk_container_set_border_width (GTK_CONTAINER (content_area), 10);

  grid = frame_new (content_area, "Project");
  name = entry_new (grid, "_Name");
  description = ml_entry_new (grid, "_Description");

  grid = frame_new (content_area, "Customer");
  customer = entry_new (grid, "_Name");

  grid = frame_new (content_area, "Orders and Payments");
  orders = reference_new (grid);

  grid = frame_new (content_area, "Internal References");
  internal = reference_new (grid);

  gtk_widget_show_all (dialog);

  gint result = gtk_dialog_run (GTK_DIALOG (dialog));

  switch (result)
  {
    case GTK_RESPONSE_APPLY:
//      project_info->name = "Project";
//      project_info->description = "Project";
//      project_info->customer = "Customer";
      //project_info->name = gtk_entry_get_text (GTK_ENTRY (name));
//      project_info->description = gtk_entry_get_text (GTK_ENTRY (description));
      //project_info->customer = gtk_entry_get_text (GTK_ENTRY (customer));
//      create_project (project_info);
      break;
    default:
      break;
  }

  gtk_widget_destroy (dialog);

  return 0;
}
