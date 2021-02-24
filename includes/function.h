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
    GtkWidget        *carDate;
    GtkWidget        *carName;
    GtkWidget        *search;
    GtkWidget       *searching[2];
    GtkLabel        *test;
    GtkWidget        *plannigPlage;

    GtkWidget       ***listCheckbox;

} gtkStruct;

void NextFile(GtkButton button, gpointer user_data);
void writeName();
void gladeLoader();
void indexWindow(char *lastName, char *firstName, GtkWidget *matricule);
char *printDate();
void futureMove(GtkWidget *matricule);
void ancienMove(GtkWidget *matricule);
G_MODULE_EXPORT void exportFile();
int getNumberVehicule();
G_MODULE_EXPORT void exitApp();
void searchPlanning(GtkButton *search, gpointer tab);
char *orgaDate(char *recupDate);
char **getDateData(char *recupDate);
void updatePlanning(char *id, char *matricule, char *date, int start, int end);
void createPlanning(char ***tabReservedPlage, int nPlage);
G_MODULE_EXPORT char ***getReservedPlage(GtkWidget *widget);
void setUnavailablePlage(char **dateData, char *txtBegin, char *txtEnd, int startDay);


#endif //PARKHOUR_FUNCTION_H
