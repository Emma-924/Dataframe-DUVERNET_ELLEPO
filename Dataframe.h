//
// Created by Emma DUVERNET on 28/03/2024.
//

#ifndef PROJET_S2_DATAFRAME_DATAFRAME_H
#define PROJET_S2_DATAFRAME_DATAFRAME_H

#define REALLOC_SIZE 256
typedef struct {
    char titre[100];
    int taille_physique;
    int taille_logique;
    int tab[];
}COLUMN;




COLUMN *create_column(char* title);
int insert_value(COLUMN* col, int value);
void delete_column(COLUMN **col);
void print_col(COLUMN* col);
void change_name_col(COLUMN* col,char* new_title);
int nb_occ(COLUMN* col,int x);
int nb_occ_sup(COLUMN* col,int x);
int nb_occ_inf(COLUMN* col,int x);
int val_at_pos(COLUMN* col,int x);







#endif //PROJET_S2_DATAFRAME_DATAFRAME_H
