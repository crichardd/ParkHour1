//
// Created by Chloé RICHARD on 16/01/2021.
//

#ifndef PARKHOUR_FUNCTION_H
#define PARKHOUR_FUNCTION_H

#define G_MODULE_EXPORT __declspec(dllexport)

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
    GtkLabel        *after;
    GtkLabel        *before;
    GtkWidget        *export;
    GtkWidget        *deco;



} gtkStruct;



void NextFile(GtkButton button, gpointer user_data);
void writeName();
void gladeLoader();
void indexWindow(char *lastName, char *firstName, GtkWidget *matricule);
void printDate();
void futureMove(matricule);
void ancienMove(matricule);
void exportFile();
int getNumberVehicule();
void exitApp();

#endif //PARKHOUR_FUNCTION_H
