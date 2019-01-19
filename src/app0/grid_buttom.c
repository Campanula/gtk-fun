#include <gtk/gtk.h>

static void print_hello(GtkButton *widget, gpointer data)
{
    g_print("%s: Hello World!\n", gtk_button_get_label(widget));
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
  // 设置边框大小
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  grid = gtk_grid_new();
  buttom_1 = gtk_button_new_with_label("Hellow 1");
  buttom_2 = gtk_button_new_with_label("Hellow 2");
  buttom_3 = gtk_button_new_with_label("Quit");

  gtk_container_add(GTK_CONTAINER(window), grid);
  // 4个数字参数分别是定位坐标(x,y) 和 宽高(w,h)
  gtk_grid_attach(GTK_GRID(grid), buttom_1, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), buttom_2, 1, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), buttom_3, 0, 1, 2, 1);

  gtk_widget_set_can_default(buttom_1, TRUE);
  gtk_widget_grab_default(buttom_1);

  // callback 指定函数，函数的第一个参数是部件本身，第二个参数是要传递的数据
  g_signal_connect(buttom_1, "clicked", G_CALLBACK(print_hello), NULL);
  g_signal_connect(buttom_2, "clicked", G_CALLBACK(print_hello), NULL);
  g_signal_connect_swapped(buttom_3, "clicked", G_CALLBACK(gtk_widget_destroy), window);

  // 递归显示所有子部件
  gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
  int status;
  GtkApplication *app;

  // see https://wiki.gnome.org/HowDoI/GtkApplication
  app = gtk_application_new("com.github.companula.gtk-fun-1", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
