//
// Created by Emma DUVERNET on 28/03/2024.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dataframe.h"


COLUMN *create_column(char* title){
    // initialise les données de la colonne

    COLUMN *column=malloc(sizeof (COLUMN));
    strcpy(column->titre,title);
    column->taille_logique = 0;
    column->taille_physique = 0;
    column->tab = NULL;

    return column;

}

int insert_value(COLUMN* col, int value){
    // permet d'ajouter une valeur dans une colonne
    int valeur_retour = 0;

    if (col->taille_logique + 1 > col->taille_physique){
        // rajoute de l'espace si necessaire
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
        // si l'espace est suffisant, on ajoute
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
    // supprime une colonne

    free((*col)->tab);
    free(*col);
}



void print_col(COLUMN* col){
    // affiche une colonne
    for (int i=0;i<col->taille_logique;i++) {
        printf("[%d] \t%d\n", i, col->tab[i]);
    }
}


void change_name_col(CDATAFRAME *data,int n,char* new_title) {
    // permet de changer le nom d'une colonne
    if (data->nb_col == 0)
        printf("Aucune colonne n'a été trouvée");
    else
        strcpy(data->col_tab[n], new_title);
}

void delete_column_from_databse(CDATAFRAME* data, int n){
    // permet de supprimer une colonne de la base de donnée
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
    // retourne le nombre d'occurence égale à x
    int nb = 0,i ;
    for (i=0;i<col->taille_logique;i++){
        if(col->tab[i] == x){
            nb++;
        }
    }
    return nb;
}

int nb_occ_greater(COLUMN* col,int x){
    //retourne le nombre d'occurence supérieure à x
    int nb = 0;
    for (int i=0;i<col->taille_logique;i++){
        if(col->tab[i] > x)
        nb++;
    }
    return nb;
}

int nb_occ_lower(COLUMN* col,int x){
    //retourne le nombre d'occurence inférieure à x
    int nb = 0;
    for (int i=0;i<col->taille_logique;i++){
        if(col->tab[i] < x) nb++;
    }
    return nb;
}

int val_at_pos(COLUMN* col,int x){
    // renvoie la valeur située à la position x
    return col->tab[x];
}


CDATAFRAME *create_dataframe(){
    // initialise les données de la base de donnée
    CDATAFRAME *data=malloc (sizeof (CDATAFRAME));
    data->nb_col = 0;
    data->nb_row = 0; // Toutes les colonnes ont le même nombres de lignes
    data->col_tab = NULL;
    printf("Dataframe créé avec succès");
    return data;

}

int add_column(CDATAFRAME * data, char* title){
    // permet d'ajouter une colonne vide à la base de donnée

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
    //affiche l'entierté de la base de donnée
    COLUMN **t = data->col_tab;
    int n = data->nb_col;
    for (int i = 0; i < n; i++) {
        printf("\n\t%s\t\t\n",t[i]->titre);

        for (int j = 0; j < t[i]->taille_logique; j++) {
            printf("[%d]\t\t%d\n", j,t[i]->tab[j]);

        }
    }
}




void print_name_column_database(COLUMN *t[]  ,int n) {
    // affiche le nom des colonnes de la base de donnée
    for (int i = 0; i < n; i++) {
        printf("-%s\n", t[i]->titre);
    }
}


int check_value_in_database(CDATAFRAME* data, int n){
    //vérifie si une valeur est présente dans la base de donnée
    int i ;
    for (i = 0; i< data->nb_col;i++){
        if (nb_occ(data->col_tab[i],n)!=0){
            // regarde si la valeur est présente dans chque colonne grâce à la fonction créée
            printf("La valeur a été trouvée dans le tableau \n");
            return 1;
        }
    }
    printf("La valeur n'a pas été trouvée dans le tableau\n");
    return 0;
}

void change_database_value(CDATAFRAME* data, int col, int row, int val) {
    // permet de changer une valeur de la base de donnée
    data->col_tab[col]->tab[row] = val;
}

int nb_occ_in_database(CDATAFRAME* data, int val){
    // renvoie le nombre de valeurs égales à val présentes dans la base de données
    int i, nb = 0 ;
    for (i = 0; i< data->nb_col;i++){
        // compte le nombre de valeurs égales à val dans chaque colonne grâce à la fonction définie précédemment
        nb += (nb_occ(data->col_tab[i],val));
    }
    return nb;
}

int nb_occ_greater_in_database(CDATAFRAME* data, int val){
    // renvoie le nombre de valeurs supérieures à val présentes dans la base de données
    int i, nb = 0 ;
    for (i = 0; i< data->nb_col;i++){
        // compte le nombre de valeurs supérieures à val dans chaque colonne grâce à la fonction définie précédemment
        nb += (nb_occ_greater(data->col_tab[i],val));
    }
    return nb;
}

int nb_occ_lower_in_database(CDATAFRAME* data, int val){
    // renvoie le nombre de valeurs inférieures à val présentes dans la base de données
    int i, nb = 0 ;
    for (i = 0; i< data->nb_col;i++){
        // compte le nombre de valeurs inférieures à val dans chaque colonne grâce à la fonction définie précédemment
        nb += (nb_occ_lower(data->col_tab[i],val));
    }
    return nb;
}

void delete_row(COLUMN* col,int n){
    // supprime une ligne d'une colonne
    for (int i = n; i < col-> taille_logique ; i++)
        col->tab[i] = col->tab[i+1];
    col-> taille_logique--;

}

void database_delete_row(CDATAFRAME* data, int n){
    // supprime une ligne de valeur de la base de données
    for(int i = 0; i < data->nb_col; i++){
        // supprime chaque élément de la ligne selectionnée
        delete_row(data->col_tab[i],n) ;
    }
    data->nb_row--;
}

void add_row_to_database(CDATAFRAME* data){
    // ajoute une ligne de valeur à la base de donnée
    int val;
    for (int i = 0; i < data->nb_col;i++) {
        printf("\tAjout à la colonne %d :\n",i);
        printf("\nSaisir la valeur à ajouter : ");
        scanf("%d", &val);
        insert_value(data->col_tab[i], val);
        data->nb_row++;

    }
}

void some_column(CDATAFRAME* data, int inf, int sup){
    // affiche les colonnes comprises dans l'intervalle inf,sup
    for (int i = inf ; i < sup; i++){
        printf("\t\t%s\n",data->col_tab[i]->titre);
        print_col(data->col_tab[i]);
    }
}


void some_row(CDATAFRAME* data, int inf, int sup){
    // affiche les lignes comprises dans l'intervalle inf,sup
    for (int i = 0; i < data->nb_col; i++) {
        printf("\t\t%s\n",data->col_tab[i]->titre);
        for (int j = inf; j < sup ; j++) {
            printf("[%d]\t\t %d\n",j,data->col_tab[i]->tab[j]);
        }
    }
}


// fonctions pour chaque fonctionnalité
void analyse_statistiques(CDATAFRAME** data){
    int choice_menu, val;

    printf("\tAnalyse et statistiques\n\n");
    printf("1. \tAfficher le nombre de lignes\n"
           "2. \tAfficher le nombre de colonnes\n"
           "3. \tNombre de cellules contenant une valeur égale à x (x donné en paramètre)\n"
           "4. \tNombre de cellules contenant une valeur supérieure à x (x donné en paramètre)\n"
           "5. \tNombre de cellules contenant une valeur inférieure à x (x donné en paramètre)\n");
    scanf("%d", &choice_menu);

    switch (choice_menu) {
        case 1 :
            printf("Il y a %d ligne(s)",(*data)->nb_row);
            break;

        case 2 :
            printf("Il y a %d colonne(s)",(*data)->nb_col);
            break;

        case 3 :
            printf("Veuillez saisir une valeur : \n");
            scanf("%d",&val);
            if (nb_occ_in_database(*data,val)!= 0)
                printf("La valeur %d a été trouvée %d fois\n",val,nb_occ_in_database(*data,val));
            if (nb_occ_in_database(*data,val)== 0)
                printf("La valeur %d n'a pas été trouvée\n ",val);
            break;

        case 4:
            printf("Veuillez saisir une valeur : \n");
            scanf("%d",&val);
            if (nb_occ_greater_in_database(*data,val)>1)
                printf("%d valeurs supérieures à %d ont été trouvées\n",nb_occ_greater_in_database(*data,val),val);
            else if (nb_occ_greater_in_database(*data,val) == 1)
                printf("%d valeur supérieure à %d à été trouvée\n",nb_occ_greater_in_database(*data,val),val);
            else if (nb_occ_greater_in_database(*data,val) == 0)
                printf("Aucune valeur supérieure à %d n'à été trouvée\n",val);
            break;

        case 5:
            printf("Veuillez saisir une valeur : \n");
            scanf("%d",&val);
            if (nb_occ_lower_in_database(*data,val)>1)
                printf("%d valeurs inférieures à %d ont été trouvées\n",nb_occ_lower_in_database(*data,val),val);
            else if (nb_occ_lower_in_database(*data,val)==1)
                printf("%d valeur inférieure à %d à été trouvée\n",nb_occ_lower_in_database(*data,val),val);
            else if (nb_occ_lower_in_database(*data,val)==0)
                printf("Aucune valeur inférieure à %d n'à été trouvée\n",val);
            break;

        default :
            printf("Valeur invalide");

    }
}


void alimentation(CDATAFRAME** data){
    int choice_menu, second_choice_menu, nb = 0, nb_col, val, nb_row, inf, sup;
    char nom_col[100] ;

    printf("\t\tAlimentation\n\n");
    printf("1. \tCréation d’un CDataframe vide\n"
           "2. \tRemplissage du CDataframe à partir de saisies utilisateurs\n"
           "3. \tRemplissage en dur du CDataframe\n");
    scanf("%d", &choice_menu);

    switch (choice_menu) {
        case 1:
            printf("\n");
            *data = create_dataframe();
            break;

        case 2:
            printf("Saisir le nombre de colonnes souhaité : \n");
            scanf("%d",&nb_col);
            printf("Saisir le nombre de lignes souhaité : \n");
            scanf("%d",&nb_row);
            (*data)->nb_row += nb_row;

            for(int i = 0; i<nb_col;i++){
                printf("Saisir le nom de la colonne %d : \n",i+1);
                scanf("%s",nom_col);
                add_column(*data,nom_col);
            }
            for(int i = 0; i<nb_col;i++){
                printf("\tRemplissage de la colonne %d\n", i+1);
                for(int j = 0; j<nb_row;j++) {
                    printf("Saisir une valeur : \n");
                    scanf("%d",&val);
                     insert_value((*data)->col_tab[i],val);
                }
            }
            printf("\tFin du remplissage\n");
            break;
    }

}


void affichage(CDATAFRAME** data){
    int choice_menu, inf, sup ;

    printf("\t\tAffichage\n\n");
    printf("1. \tAfficher tout le CDataframe\n"
           "2. \tAfficher une partie des lignes du CDataframe selon une limite fournie par l’utilisateur\n"
           "3. \tAfficher une partie des colonnes du CDataframe selon une limite fournie par l’utilisateur\n");
    scanf("%d", &choice_menu);

    switch (choice_menu) {
        case 1:
            if (*data == NULL)
                printf("Aucune données");
            else
                print_database(*data);
            break;
        case 2 :
            printf("Sasir la borne inferieure : ");
            scanf("%d",&inf);
            printf("Sasir la borne superieure : ");
            scanf("%d",&sup);
            some_row(*data,inf,sup);
            break;

        case 3:
            printf("Sasir la borne inferieure : ");
            scanf("%d",&inf);
            printf("Sasir la borne superieure : ");
            scanf("%d",&sup);
            some_column(*data,inf,sup);
            break;
    }
}



void operations_usuelles(CDATAFRAME** data){
    int choice_menu, val, nb_col, nb_row;
    char nom_col[100], new_col_name[100];

    printf("\tOpérations usuelles\n\n");
    printf("1. \tAjouter une ligne de valeurs au CDataframe\n"
           "2. \tSupprimer une ligne de valeurs du CDataframe\n"
           "3. \tAjouter une colonne au CDataframe\n"
           "4. \tSupprimer une colonne du CDataframe\n"
           "5. \tRenommer le titre d’une colonne du CDataframe\n"
           "6. \tVérifier l’existence d’une valeur (recherche) dans le CDataframe\n"
           "7. \tAccéder/remplacer la valeur se trouvant dans une cellule du CDataframe en utilisant son numéro de ligne et de colonne\n"
           "8. \tAfficher les noms des colonnes\n");
    scanf("%d", &choice_menu);

    switch (choice_menu) {
        case 1 :
            if ((*data)->nb_col == 0)
                printf("Aucune colonne trouvée, l'ajout n'a pas été effectué ");
            else {
                add_row_to_database(*data);
            }
            break;

        case 2 :
            if ((*data)->nb_row == 0) {
                printf("Aucune ligne trouvée");
                printf("Saisir la ligne à supprimer : \n");
                scanf("%d", &val);
            }
            else {
                database_delete_row(*data, val);
            }
            break;

        case 3:
            printf("Veuillez saisir le nom de la colonne : \n");
            scanf("%s", nom_col);
            add_column(*data, nom_col);
            break;

        case 4:
            for (int i = 0; i < (*data)->nb_col; i++) {
                printf("[%d] %s\n", i, (*data)->col_tab[i]->titre);
            }
            printf("Veuillez saisir le numéro de la colonne à effacer : \n");
            scanf("%d",&nb_col);
            delete_column_from_databse(*data,nb_col);
            break;

        case 5:
            for (int i = 0; i < (*data)->nb_col; i++) {
                printf("[%d] %s\n", i, (*data)->col_tab[i]->titre);
            }
            printf("Veuillez saisir le numéro actuel de la colonne : \n");
            scanf("%d",&nb_col);
            printf("Veuillez saisir le nouveau nom de la colonne : ");
            scanf("%s",new_col_name);
            change_name_col(*data,nb_col,new_col_name);
            break;

        case 6:
            printf("Saisir la valeur à rechercher dans le tableau : \n");
            scanf("%d",&val);
            check_value_in_database(*data, val);
            break;

        case 7:
            printf("Veuillez saisir le numéro de la colonne de la valeur: \n");
            scanf("%d",&nb_col);
            printf("Veuillez saisir le numéro de la ligne de la valeur : ");
            scanf("%d",&nb_row);
            printf("Veuillez saisir la nouvelle valeur : \n");
            scanf("%d",&val);
            change_database_value(*data,nb_col,nb_row,val);
            break;

        case 8:
            print_name_column_database((*data)->col_tab, (*data)->nb_col);
            break;

    }
}
