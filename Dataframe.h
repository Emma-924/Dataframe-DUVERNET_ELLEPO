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








#endif //PROJET_S2_DATAFRAME_DATAFRAME_H
