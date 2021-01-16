//
// Created by Chloé RICHARD on 16/01/2021.
//

#include <function.h>

// Creation fonction connexion bdd avec return

// Creation fonction injection sql avec return

void NextFile(GtkButton button, gpointer tab){

    GtkWidget **tab2= (GtkWidget*)tab;

    printf("%p %p**\n", tab2[0], tab2[1] );

    GtkWidget *matricule = ((GtkWidget**) tab)[0];
    GtkWidget *pwd = ((GtkWidget**) tab)[1];

    printf("%p %p**\n", matricule, pwd );

}

