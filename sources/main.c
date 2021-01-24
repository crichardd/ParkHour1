#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include <function.h>

void abcd(GtkWidget *object, gpointer user_data)
{
    int *i = (int*)user_data;
    gtk_main_quit();

    printf("%d", *i);
}


int main(int argc, char **argv) {

    GtkBuilder      *builder;
    GtkWidget       *window;
    GtkWidget       *button;
    GtkWidget       *tab[2];


    // AFFICHER accueil

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "../gtk/build.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main")); //revoir widget
    button = GTK_WIDGET(gtk_builder_get_object(builder, "button1")); //revoir widget
    tab[0] = GTK_WIDGET(gtk_builder_get_object(builder, "matricule")); //revoir widget
    tab[1] = GTK_WIDGET(gtk_builder_get_object(builder, "pwd")); //revoir widget

    printf("%p %p**\n", tab[0], tab[1] );
    //printf("%s \n", gtk_widget_show( tab[0]));

    gtk_builder_connect_signals(builder, NULL); //charger des signals depuis de builder
    g_signal_connect(button, "clicked", G_CALLBACK(NextFile), tab); //NULL --> passer une @ddr

    g_object_unref(builder); //retirer de la mémoire / avant de lancer la callback

    gtk_widget_show(window);

    gtk_main();

    return 0;

}

G_MODULE_EXPORT void on_window_main_destroy()
{
    gtk_main_quit();
}

