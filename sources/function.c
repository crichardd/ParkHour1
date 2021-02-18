//
// Created by Chloé RICHARD on 16/01/2021.
//

#include <function.h>

gtkStruct env;

// Creation fonction connexion bdd avec return
int connec_bdd(MYSQL *mysql){

    mysql_init(mysql);

    if(mysql_real_connect(mysql, "localhost", "root", "root", "parkhour", 3306, NULL, 0))
    {
        printf("bdd ok!\n");
        return 1;
    }

    return 0;
}

// Creation fonction injection sql avec return

//connexion
void NextFile(GtkButton button, gpointer tab){

    char query[256];
    MYSQL mysql;
    MYSQL_RES *info_all;
    MYSQL_ROW try;

    GtkWidget **tab2= (GtkWidget*)tab;

    GtkWidget *matricule = ((GtkWidget**) tab)[0];
    GtkWidget *pwd = ((GtkWidget**) tab)[1];

    if(connec_bdd(&mysql)){
        strcpy(query, "SELECT pwd, nom, prenom FROM usager WHERE matricule = ");
        strcat(query, gtk_entry_get_text(GTK_ENTRY (matricule)));
        mysql_query(&mysql, query);

        info_all = mysql_store_result(&mysql);
        if(info_all){
            try = mysql_fetch_row( info_all);
            if(try)
              printf("%s\n", try[0]);
        }else{
            printf("ALED");
        }
        mysql_close(&mysql);
    }

    if(strcmp(gtk_entry_get_text(GTK_ENTRY(pwd)), try[0]) == 0){
        printf("mdp ok\n");
        indexWindow(try[1], try[2]);
    } else {
        printf("mdp not ok\n");
    }

}

void indexWindow(char *lastName, char *firstName){

    gtk_widget_hide(env.window); //cache window
    gtk_widget_show(env.index);

    writeName(lastName, firstName);
    printDate();

}
void writeName(char *lastName, char *firstName){

    char *fullName;
    fullName = malloc(sizeof(char)*256);

    strcpy(fullName, "Bonjour, ");
    strcat(fullName, lastName);
    strcat(fullName, " ");
    strcat(fullName, firstName);

    gtk_label_set_text(env.name, fullName);

}

void printDate(){

    int day, month, years;
    char *Tdate;
    char *timeToStr;
    time_t now;


    Tdate = malloc(sizeof(char)*256);
    timeToStr = malloc(sizeof(char)*10);

    // Renvoie l'heure actuelle
    time(&now);
    // Convertir au format heure locale
    struct tm *local = localtime(&now);
    day = local->tm_mday;
    month = local->tm_mon + 1;
    years = local->tm_year + 1900;
    itoa(day, timeToStr, 10);
    strcpy(Tdate, timeToStr);
    strcat(Tdate, "/");
    itoa(month, timeToStr, 10);
    strcat(Tdate, timeToStr);
    strcat(Tdate, "/");
    itoa(years, timeToStr, 10);
    strcat(Tdate, timeToStr);

    gtk_label_set_text(env.todayDate, Tdate);

}

void gladeLoader(){

    env.builder = gtk_builder_new();
    gtk_builder_add_from_file (env.builder, "../gtk/build.glade", NULL);

    //fenetre 1
    env.window = GTK_WIDGET(gtk_builder_get_object(env.builder, "window_main")); //appel la page window_main
    env.button = GTK_WIDGET(gtk_builder_get_object(env.builder, "button1")); //revoir widget
    env.tab[0] = GTK_WIDGET(gtk_builder_get_object(env.builder, "matricule")); //revoir widget
    env.tab[1] = GTK_WIDGET(gtk_builder_get_object(env.builder, "pwd")); //revoir widget

    //fenetre 2
    env.index = GTK_WIDGET(gtk_builder_get_object(env.builder, "window_index"));//appel la page window_index
    env.name = GTK_LABEL(gtk_builder_get_object(env.builder, "nameLabel")); //le label
    env.todayDate = GTK_LABEL(gtk_builder_get_object(env.builder, "dateLabel"));//appel la page window_index

    gtk_builder_connect_signals(env.builder, NULL); //charger des signals depuis de builder
    g_signal_connect(env.button, "clicked", G_CALLBACK(NextFile), env.tab); //NULL --> passer une @ddr

    g_object_unref(env.builder); //retirer de la mémoire / avant de lancer la callback
}

/*
 // Creation fonction connexion bdd avec return
int connec_bdd(MYSQL *mysql){
   // MYSQL mysql;

    //char query[256];


    mysql_init(mysql);
    // mysql_options(mysql,MYSQL_READ_DEFAULT_GROUP,"option");

    if(mysql_real_connect(mysql, "localhost", "root", "root", "parkhour", 3306, NULL, 0))
    {
        printf("bdd ok!\n");

        //strcpy(query, "insert into usager (matricule, pwd, nom, prenom, poste, type) VALUES ('2', 'Chlochlo77', 'richard', 'chloe', 'infirmier', '1')");
        //mysql_query(&mysql, query);

        return 1;
    }

    return 0;
}*/