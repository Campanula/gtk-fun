#include <gtk/gtk.h>

static void print_hello(GtkWidget *widget, gpointer data)
{
    g_print("Hello World!\n");
}

static void activate(GtkApplication* app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *buttom_1;
  GtkWidget *buttom_2;
  GtkWidget *buttom_3;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "GTK-fun");
  //gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  grid = gtk_grid_new();
  buttom_1 = gtk_button_new_with_label("Hellow World1");
  buttom_2 = gtk_button_new_with_label("Hellow World2");
  buttom_3 = gtk_button_new_with_label("Quit");

  gtk_container_add(GTK_CONTAINER(window), grid);
  gtk_grid_attach(GTK_GRID(grid), buttom_1, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), buttom_2, 1, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), buttom_3, 0, 1, 2, 1);

  gtk_widget_set_can_default(buttom_1, TRUE);
  gtk_widget_grab_default(buttom_1);

  g_signal_connect(buttom_1, "clicked", G_CALLBACK(print_hello), NULL);
  g_signal_connect(buttom_2, "clicked", G_CALLBACK(print_hello), NULL);
  g_signal_connect_swapped(buttom_3, "clicked", G_CALLBACK(gtk_widget_destroy), window);

  gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
  int status;
  GtkApplication *app;

  app = gtk_application_new("org.desktop-crafts.gtk-fun", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
