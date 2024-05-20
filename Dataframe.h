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
    int *tab;
}COLUMN;

typedef struct {
    int nb_col;
    int nb_row;
    COLUMN **col_tab;
}CDATAFRAME;


COLUMN *create_column(char* title);
int insert_value(COLUMN* col, int value);
void delete_column(COLUMN **col);
void print_col(COLUMN* col);
void change_name_col(CDATAFRAME *data,int n,char* new_title);

int nb_occ(COLUMN* col,int x);
int nb_occ_greater(COLUMN* col,int x);
int nb_occ_lower(COLUMN* col,int x);
int val_at_pos(COLUMN* col,int x);

CDATAFRAME *create_dataframe();
int add_column(CDATAFRAME * data, char* title);
void print_database(CDATAFRAME * data);
void print_name_column_database(COLUMN *t[]  ,int n);
void delete_column_from_databse(CDATAFRAME* data, int n);
int check_value_in_database(CDATAFRAME* data, int n);
void change_database_value(CDATAFRAME* data, int col, int row, int val);
int nb_occ_in_database(CDATAFRAME* data, int val);
int nb_occ_greater_in_database(CDATAFRAME* data, int val);
int nb_occ_lower_in_database(CDATAFRAME* data, int val);
void delete_row(COLUMN* col,int n);
void database_delete_row(CDATAFRAME* data, int n);
void add_row_to_database(CDATAFRAME* data);
void some_row(CDATAFRAME* data, int inf, int sup);
void some_column(CDATAFRAME* data, int inf, int sup);

void analyse_statistiques(CDATAFRAME** data);
void alimentation(CDATAFRAME** data);
void affichage(CDATAFRAME** data);
void operations_usuelles(CDATAFRAME** data);



#endif //PROJET_S2_DATAFRAME_DATAFRAME_H

