//
// Created by Chloé RICHARD on 16/01/2021.
//

#include <function.h>

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
        strcpy(query, "SELECT pwd FROM usager WHERE matricule = ");
        strcat(query, gtk_entry_get_text(GTK_ENTRY (matricule)));

        mysql_query(&mysql, query);

        info_all = mysql_store_result(&mysql);
        if(info_all){
            try = mysql_fetch_row( info_all);
            printf("%s\n", try[0]);
        }else{
            printf("ALED");
        }
        mysql_close(&mysql);
    }

    if(strcmp(gtk_entry_get_text(GTK_ENTRY(pwd)), try[0]) == 0){
        printf("mdp ok\n");
    } else {
        printf("mdp not ok\n");
    }

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