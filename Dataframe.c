//
// Created by Emma DUVERNET on 28/03/2024.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dataframe.h"


COLUMN *create_column(char* title){

    COLUMN *column=malloc(sizeof (COLUMN));
    strcpy(column->titre,title);
    column->taille_logique = 0;
    column->taille_physique = 0;
    column->tab = NULL;

    return column;

}

int insert_value(COLUMN* col, int value){
    int valeur_retour = 0;

    if (col->taille_logique + 1 > col->taille_physique){
        if (col->taille_physique == 0) {
            col->tab = malloc(256 * sizeof(int));
            col->taille_physique = 256;
        }
        else if (col->taille_physique >= 256){
            col->tab = realloc(col->tab,256 * sizeof(int));
            col->taille_physique += 256;
        }
    }

    if (col->tab != NULL){
        col->tab[col->taille_logique] = value;
        col->taille_logique ++;
        valeur_retour = 1;
    } else
        valeur_retour = 0;

    return valeur_retour;
}

void delete_column(COLUMN **col){

    free((*col)->tab);
    free(*col);
}




void print_col(COLUMN* col){
    for (int i=0;i<col->taille_logique;i++)
        printf("[%d] \t%d\n",i,col->tab[i]);
}

void change_name_col(COLUMN* col,char* new_title){
    strcpy(col->titre,new_title);
}


int nb_occ(COLUMN* col,int x){
    int nb = 0,i ;
    for (i=0;i<col->taille_logique;i++){
        if(col->tab[i] == x){
            nb++;
        }
    }
    return nb;
}

int nb_occ_sup(COLUMN* col,int x){
    int nb = 0;
    for (int i=0;i<col->taille_logique;i++){
        if(col->tab[i] > x)
        nb++;
    }
    return nb;
}

int nb_occ_inf(COLUMN* col,int x){
    int nb = 0;
    for (int i=0;i<col->taille_logique;i++){
        if(col->tab[i] < x) nb++;
    }
    return nb;
}

int val_at_pos(COLUMN* col,int x){
    return col->tab[x];
}
