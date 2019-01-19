#include <gtk/gtk.h>

static void print_hello(GtkWidget *widget, gpointer *data)
{
    g_print("Hello World\n");
}

int main(int argc, char *argv[])
{
    GtkBuilder *builder;
    GObject *window;
    GObject *button1;
    GObject *button2;
    GObject *button3;
    GError *error = NULL;
    
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    if(gtk_builder_add_from_file(builder, "builder.ui", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    window = gtk_builder_get_object(builder, "window");
    button1 = gtk_builder_get_object(builder, "button1");
    button2 = gtk_builder_get_object(builder, "button2");
    button3 = gtk_builder_get_object(builder, "quit");

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(button1, "clicked", G_CALLBACK(print_hello), NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(print_hello), NULL);
    g_signal_connect(button3, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_main();
    return 0;
}
