//
// Created by Chloé RICHARD on 16/01/2021.
//

#include <function.h>

#define RAPPORTFILENAME "./rapport.txt"

gtkStruct env;

// Creation fonction connexion bdd avec return
int connec_bdd(MYSQL *mysql){

    mysql_init(mysql);

    if(mysql_real_connect(mysql, "localhost", "root", "root", "parkhour", 3306, NULL, 0))
    {
        printf("bdd ok!\n");
        return 1;
    }else{
        printf("sos");
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

    GtkWidget *tab2= (GtkWidget*)tab;

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
        indexWindow(try[1], try[2], matricule);
    } else {
        printf("mdp not ok\n");
    }

}

void indexWindow(char *lastName, char *firstName, GtkWidget *matricule){

    gtk_widget_hide(env.window); //cache window
    gtk_widget_show(env.index);

    char *Tdate;

    Tdate = malloc(sizeof(char)*256);

    writeName(lastName, firstName);
    Tdate = printDate();

    gtk_label_set_text(env.todayDate, Tdate);

    futureMove(matricule);
    ancienMove(matricule);
   // exportFile();
    //exitApp();

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

char *printDate(){

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

    //gtk_label_set_text(env.todayDate, Tdate);

    return Tdate;
}

void futureMove(GtkWidget *matricule){

    char query[256];
    MYSQL mysql;
    MYSQL_RES *info_all;
    MYSQL_ROW stock;
    char *data;

    data = malloc(sizeof(char)*256);

    if(connec_bdd(&mysql)){
        strcpy(query, "SELECT debut, vehicule FROM deplacement INNER JOIN participant ON participant.deplacement = deplacement.matricule WHERE debut>NOW() AND participant.matricule = ");
        strcat(query, gtk_entry_get_text(GTK_ENTRY (matricule)));
        strcat(query, " ORDER BY debut ASC");
        mysql_query(&mysql, query);

        info_all = mysql_store_result(&mysql);
        if(info_all){
            stock = mysql_fetch_row( info_all );
            strcpy(data, stock[0]);
            strcat(data, "\n");
            strcat(data, stock[1]);
            strcat(data, "\n");

            gtk_label_set_text(env.after, data);

        }else{
            printf("Pas ok");
        }

        mysql_close(&mysql);
    }
}

void ancienMove(GtkWidget *matricule){

    char query[256];
    MYSQL mysql;
    MYSQL_RES *info_all;
    MYSQL_ROW stock;
    char *data;

    data = malloc(sizeof(char)*256);

    if(connec_bdd(&mysql)){
        strcpy(query, "SELECT debut, vehicule FROM deplacement INNER JOIN participant ON participant.deplacement = deplacement.matricule WHERE debut<NOW() AND participant.matricule = ");
        strcat(query, gtk_entry_get_text(GTK_ENTRY (matricule)));
        strcat(query, " ORDER BY debut ASC");
        mysql_query(&mysql, query);

        info_all = mysql_store_result(&mysql);
        if(info_all){
            stock = mysql_fetch_row( info_all);
        }else{
            printf("Pas ok");
        }

        strcpy(data, stock[0]);
        strcat(data, "\n");
        strcat(data, stock[1]);
        strcat(data, "\n");

        gtk_label_set_text(env.before, data);

        mysql_close(&mysql);
    }

}
/*
int getNumberVehicule(){
    FILE *fp;
    char buffer;
    int count;

    fp = fopen(RAPPORTFILENAME, "rb");

    if(fp)
    {
        count = 0;
        while(fread(&buffer, sizeof(char), 1, fp), !feof(fp))
        {
            if(buffer == '\n')
                count++;
        }

        fclose(fp);
        return count;
    }

    fclose(fp);
    return -1;
}*/

G_MODULE_EXPORT void exportFile(){

    char query[256];
    MYSQL mysql;
    MYSQL_RES *info_all;
    MYSQL_ROW row;
    FILE *fp;
    int nb = 1;

    printf("aleed svp");
    if(connec_bdd(&mysql)){

        strcpy(query, "SELECT immatriculation, type, kilometrage, observation, revision FROM vehicules ORDER BY revision ASC");
        mysql_query(&mysql, query);

        fp = fopen(RAPPORTFILENAME, "a");

        if(fp){
            printf("chk trigger!\n");
            info_all = mysql_store_result(&mysql);
           // row = mysql_fetch_row( info_all);
            while(row = mysql_fetch_row( info_all )){
                fprintf(fp, "Vehicule %d :", nb);
                fprintf(fp, " %s |", row[0]);
                fprintf(fp, " %s |", row[1]);
                fprintf(fp, " %s |", row[2]);
                fprintf(fp, " %s |", row[3]);
                fprintf(fp, " %s \n", row[4]);
                nb += 1;
            }
            fclose(fp);
        }
        mysql_close(&mysql);
    }
}

G_MODULE_EXPORT void exitApp(){
    gtk_widget_hide(env.index); //cache index
    gtk_widget_show(env.window); //cache window
}

void searchPlanning(GtkButton *search, gpointer tab){
    char query[256];
    MYSQL mysql;
    MYSQL_RES *info_all;
    MYSQL_ROW try;
    char *Tdate;
    char *structDate;
    char * recupDate ;

    Tdate = malloc(sizeof(char)*256);
    structDate = malloc(sizeof(char)*256);

    GtkWidget **searching= (GtkWidget**)tab;

    if(connec_bdd(&mysql)){
        strcpy(query, "SELECT debut, fin FROM deplacement WHERE vehicule = '");
        strcat(query, gtk_entry_get_text(GTK_ENTRY (env.carName)));
        strcat(query, "' AND '");
        strcat(query, gtk_entry_get_text(GTK_ENTRY (env.carDate)));
        strcat(query, "'>=NOW()");
        mysql_query(&mysql, query);
        printf("%s\n", query);

        info_all = mysql_store_result(&mysql);
        if(info_all){
            try = mysql_fetch_row( info_all);
            if(try){
                printf("\n%s\n", try[0]);
                gtk_label_set_text(env.test, try[0]);
            }
        }

        recupDate = try[0];
        structDate = orgaDate(recupDate);
        Tdate = printDate();
        if(structDate != Tdate)
            printf("1");
        else
            printf("0");
        mysql_close(&mysql);
    }

   // if(try[0] != ){

    //}
}

char *orgaDate(char *recupDate){

    printf("%s\n", recupDate);
    char *nextSeparator;
    int positionRecupDate;
    int year;
    char stockDate[3][5];
    int dateCategory;
    char * totalDate;
    totalDate = malloc(sizeof(char)*256);

    positionRecupDate = 0;

    while(recupDate[positionRecupDate] != ' ')
        positionRecupDate++;

    recupDate[positionRecupDate] = '\0';

    printf("%s\n", recupDate);

    dateCategory = 0;
    positionRecupDate = 0 ;

    while(recupDate[positionRecupDate] != '\0'){

        if(recupDate[positionRecupDate] == '-'){
            strncpy(stockDate[dateCategory], recupDate, positionRecupDate);
            stockDate[dateCategory][positionRecupDate] = '\0';
            strcpy(recupDate, recupDate + positionRecupDate + 1);

            positionRecupDate = 0;
            dateCategory++;
        }
        positionRecupDate++;
    }

    strncpy(stockDate[dateCategory], recupDate, positionRecupDate);
    stockDate[dateCategory][positionRecupDate] = '\0';

    printf("year: %s\n", stockDate[0]);
    printf("month: %s\n", stockDate[1]);
    printf("day: %s\n", stockDate[2]);

    strcpy(totalDate, stockDate[2]);
    strcat(totalDate, "/");
    strcat(totalDate, stockDate[1]);
    strcat(totalDate, "/");
    strcat(totalDate, stockDate[0]);
    strcat(totalDate, "\n");

    printf ("%s", totalDate);
/*
    gtk_grid_attach(env.plannigPlage,
                 GtkWidget *child,
                 gint left,
                 gint top,
                 gint width,
                 gint height);
    return totalDate;*/

}
/*
    GtkWidget *vehicule = ((GtkWidget**) tab)[0];
    GtkWidget *date = ((GtkWidget**) tab)[1];
*/

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
    env.todayDate = GTK_LABEL(gtk_builder_get_object(env.builder, "dateLabel"));
    env.after = GTK_LABEL(gtk_builder_get_object(env.builder, "after"));
    env.before = GTK_LABEL(gtk_builder_get_object(env.builder, "before"));
    env.export = GTK_WIDGET(gtk_builder_get_object(env.builder, "export"));
    env.deco = GTK_WIDGET(gtk_builder_get_object(env.builder, "deco"));
    env.carName = GTK_WIDGET(gtk_builder_get_object(env.builder, "carName"));
    env.carDate = GTK_WIDGET(gtk_builder_get_object(env.builder, "carDate"));
    env.search = GTK_WIDGET(gtk_builder_get_object(env.builder, "search"));
    env.test = GTK_LABEL(gtk_builder_get_object(env.builder, "test"));
    env.plannigPlage = GTK_GRID(gtk_builder_get_object(env.builder, "plannigPlage"));

    gtk_builder_connect_signals(env.builder, NULL); //charger des signals depuis de builder
    g_signal_connect(env.button, "clicked", G_CALLBACK(NextFile), env.tab); //NULL --> passer une @ddr
    g_signal_connect(env.search, "clicked", G_CALLBACK(searchPlanning), env.searching); //NULL --> passer une @ddr

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