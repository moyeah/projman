#include <gtk/gtk.h>

#include "exitdialog.h"

gboolean
exitdialog (GtkWidget *window)
{
  GtkWidget *dialog;
  gboolean   response;

  dialog = gtk_message_dialog_new (GTK_WINDOW (window),
                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                   GTK_MESSAGE_QUESTION,
                                   GTK_BUTTONS_YES_NO,
                                   "Are you sure you want to quit?");

  gtk_window_set_title (GTK_WINDOW (dialog),
                        "Leaving application...");

  gint result = gtk_dialog_run (GTK_DIALOG (dialog));

  switch (result)
  {
    case GTK_RESPONSE_YES:
      response = FALSE;
      break;
    default:
      response = TRUE;
      break;
  }

  gtk_widget_destroy (dialog);

  return response;
}
