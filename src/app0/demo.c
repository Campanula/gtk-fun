#include <glib.h>
#include <glib/gi18n.h>
#include <gtk/gtk.h>

void quick_message(GtkWindow *parent, gchar *message) {
  GtkWidget *dialog, *label, *content_area, *button;
  GtkDialogFlags flags;

  // Create the widgets
  flags = GTK_DIALOG_DESTROY_WITH_PARENT;
  dialog = gtk_dialog_new_with_buttons("Message", parent, flags, _("_OK"),
                                       GTK_RESPONSE_NONE, NULL);
  gtk_dialog_add_button(GTK_DIALOG(dialog), _("_TEST"), GTK_RESPONSE_NONE);
  gtk_dialog_add_button(GTK_DIALOG(dialog), _("_TEST"), GTK_RESPONSE_NONE);
  gtk_dialog_add_button(GTK_DIALOG(dialog), _("_TEST"), GTK_RESPONSE_NONE);
  button = gtk_dialog_add_button(GTK_DIALOG(dialog), _("_TEST"), GTK_RESPONSE_NONE);
  gtk_style_context_add_class(gtk_widget_get_style_context(button),
                              GTK_STYLE_CLASS_DESTRUCTIVE_ACTION);
  content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
  label = gtk_label_new(message);

  // Ensure that the dialog box is destroyed when the user responds

  g_signal_connect_swapped(dialog, "response", G_CALLBACK(gtk_widget_destroy),
                           dialog);

  // Add the label, and show everything we’ve added

  gtk_container_add(GTK_CONTAINER(content_area), label);
  gtk_widget_show_all(dialog);
}

int main(int argc, char **argv) {
  gtk_init(&argc, &argv);

  GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(win), "Hello there");
  quick_message(GTK_WINDOW(win), "Hello there");
  g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_widget_show(win);

  gtk_main();
}
