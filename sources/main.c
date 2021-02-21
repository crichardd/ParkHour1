#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include <function.h>

extern gtkStruct env;


int main(int argc, char **argv) {

    // AFFICHER accueil

    gtk_init(&argc, &argv);

    printf("%p %p**\n", env.tab[0], env.tab[1]);
    printf("%p %p**\n", env.searching[0], env.searching[1]);
    //printf("%s \n", gtk_widget_show( tab[0]));

    gladeLoader();
    gtk_widget_show(env.window);

    gtk_main();

    return 0;

}

G_MODULE_EXPORT void on_window_main_destroy()
{
    gtk_main_quit();
}

