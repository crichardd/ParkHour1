//
// Created by Chloé RICHARD on 16/01/2021.
//

#ifndef PARKHOUR_FUNCTION_H
#define PARKHOUR_FUNCTION_H

#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include <stdlib.h>

typedef struct {

    GtkBuilder      *builder;
    GtkWidget       *window;
    GtkWidget       *index;
    GtkWidget       *button;
    GtkWidget       *tab[2];
    GtkLabel        *name;
    GtkLabel        *todayDate;

} gtkStruct;



void NextFile(GtkButton button, gpointer user_data);
void writeName();
void gladeLoader();
void indexWindow(char *lastName, char *firstName);
void printDate();

#endif //PARKHOUR_FUNCTION_H
