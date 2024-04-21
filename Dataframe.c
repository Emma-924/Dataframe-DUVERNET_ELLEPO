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
    } else {
        valeur_retour = 0;
        printf("Echec de l'ajout");
    }
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


void change_name_col(CDATAFRAME *data,int n,char* new_title) {
    if (data->nb_col == 0)
        printf("Aucune colonne n'a été trouvée");
    else
        strcpy(data->col_tab[n], new_title);
}

void delete_column_from_databse(CDATAFRAME* data, int n){
    if (data->nb_col == 0)
        printf("Aucune colonne n'a été trouvée");
    else {
        free((*data).col_tab[n]->tab);
        free((*data).col_tab[n]);
        printf("Les données de la colonne %d ont bien été effacées\n",n);
        data->nb_col--;
    }
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

int nb_occ_greater(COLUMN* col,int x){
    int nb = 0;
    for (int i=0;i<col->taille_logique;i++){
        if(col->tab[i] > x)
        nb++;
    }
    return nb;
}

int nb_occ_lower(COLUMN* col,int x){
    int nb = 0;
    for (int i=0;i<col->taille_logique;i++){
        if(col->tab[i] < x) nb++;
    }
    return nb;
}

int val_at_pos(COLUMN* col,int x){
    return col->tab[x];
}


CDATAFRAME *create_dataframe(){
    CDATAFRAME *data=malloc (sizeof (CDATAFRAME));
    data->nb_col = 0;
    data->nb_row = 0; // Toutes les colonnes ont le même nombres de rownes
    data->col_tab = NULL;
    printf("Dataframe créé avec succès");
    return data;

}

int add_column(CDATAFRAME * data, char* title){

    int valeur_retour = 0;

    // si data est vide (nb_col = 0), on l'initialise col_tab
    if (data->nb_col == 0)
        data->col_tab = malloc(256 * sizeof(COLUMN));

    if (data->col_tab != NULL) {
        data->col_tab[data->nb_col] = create_column(title);
        data->nb_col ++;
        valeur_retour = 1;
    } else
        valeur_retour = 0;

    return valeur_retour;
}




void print_database(CDATAFRAME *data) {
    COLUMN **t = data->col_tab;
    int n = data->nb_col;
    for (int i = 0; i < n; i++) {
        //printf("%d:\n",i);
        printf("\n\t%s\t\t\n",t[i]->titre);

        for (int j = 0; j < t[i]->taille_logique; j++) {
            printf("[%d]\t\t%d\n", j,t[i]->tab[j]);

        }
    }
}




void print_name_column_database(COLUMN *t[]  ,int n) {
    for (int i = 0; i < n; i++) {
        printf("-%s\n", t[i]->titre);
    }
}


int check_value_in_database(CDATAFRAME* data, int n){
    int i ;
    for (i = 0; i< data->nb_col;i++){
        if (nb_occ(data->col_tab[i],n)!=0){
            printf("La valeur a été trouvée dans le tableau \n");
            return 1;
        }
    }
    printf("La valeur n'a pas été trouvée dans le tableau\n");
    return 0;
}

void change_database_value(CDATAFRAME* data, int col, int row, int val) {
    data->col_tab[col]->tab[row] = val;
}

int nb_occ_in_database(CDATAFRAME* data, int val){
    int i, nb = 0 ;
    for (i = 0; i< data->nb_col;i++){
        nb += (nb_occ(data->col_tab[i],val));
    }
    return nb;
}

int nb_occ_greater_in_database(CDATAFRAME* data, int val){
    int i, nb = 0 ;
    for (i = 0; i< data->nb_col;i++){
        nb += (nb_occ_greater(data->col_tab[i],val));
    }
    return nb;
}

int nb_occ_lower_in_database(CDATAFRAME* data, int val){
    int i, nb = 0 ;
    for (i = 0; i< data->nb_col;i++){
        nb += (nb_occ_lower(data->col_tab[i],val));
    }
    return nb;
}

void delete_row(COLUMN* col,int n){
    for (int i = n; i < col-> taille_logique ; i++)
        col->tab[i] = col->tab[i+1];
    col-> taille_logique--;

}

void database_delete_row(CDATAFRAME* data, int n){
    for(int i = 0; i < data->nb_col; i++){
        delete_row(data->col_tab[i],n) ;
    }
    data->nb_row++;
}


void add_row_to_database(CDATAFRAME* data){
    int val;
    for (int i = 0; i < data->nb_col;i++) {
        printf("\tAjout à la colonne %d :\n",i);
        printf("\nSaisir la valeur à ajouter : ");
        scanf("%d", &val);
        insert_value(data->col_tab[i], val);
        data->nb_row++;

    }
}
