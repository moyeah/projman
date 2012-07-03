#include <gtk/gtk.h>

#include "newprojectgda.h"

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
orders_new (GtkWidget *grid)
{

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

  GtkTreeStore *store;
  GtkTreeIter root_iter;
  GtkTreeIter item_iter;
  GtkWidget *tree;
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;

  store = gtk_tree_store_new (N_COLUMNS,
                              G_TYPE_STRING,
                              G_TYPE_STRING,
                              G_TYPE_DOUBLE);
  gtk_tree_store_append (store, &root_iter, NULL);
  gtk_tree_store_append (store, &item_iter, &root_iter);

  tree = gtk_tree_view_new_with_model (GTK_TREE_MODEL (store));
  gtk_widget_set_hexpand (tree, TRUE);
  gtk_widget_set_vexpand (tree, TRUE);
  g_object_unref (store);

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
  orders = orders_new (grid);

  grid = frame_new (content_area, "Internal References");
  orders = orders_new (grid);

  gtk_widget_show_all (dialog);

  gint result = gtk_dialog_run (GTK_DIALOG (dialog));

  switch (result)
  {
    case GTK_RESPONSE_APPLY:
      create_project ();
      break;
    default:
      break;
  }

  gtk_widget_destroy (dialog);

  return 0;
}
