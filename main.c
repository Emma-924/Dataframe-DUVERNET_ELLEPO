#include <stdio.h>
#include "Dataframe.h"


int main() {
    
    CDATAFRAME *data ;
    int choice_menu,second_choice_menu,nb=0,nb_col,val,nb_row,inf,sup;
    char nom_col[100],new_col_name[100];

    printf("\nBonjour,"
           "\nVeuillez chosir une action à effectuer");
    while (1) {
        printf("\n");
        printf("1- Alimentation\n");
        printf("2- Affichage\n");
        printf("3- Opérations usuelles\n");
        printf("4- Analyse et statistiques\n");
        scanf("%d", &choice_menu);

        switch (choice_menu) {
            case 1:
                printf("\t\tAlimentation\n\n");
                printf("1. \tCréation d’un CDataframe vide\n"
                       "2. \tRemplissage du CDataframe à partir de saisies utilisateurs\n"
                       "3. \tRemplissage en dur du CDataframe\n");
                scanf("%d", &second_choice_menu);
                switch (second_choice_menu) {
                    case 1:
                        printf("\n");
                        data = create_dataframe();
                        break;
                    case 2:
                        printf("Saisir le nombre de colonnes souahité : \n");
                        scanf("%d",&nb_col);
                        printf("Saisir le nombre de lignes souahité : \n");
                        scanf("%d",&nb_row);
                        data->nb_row += nb_row;
                        for(int i = 0; i<nb_col;i++){
                            printf("Saisir le nom de la colonne %d : \n",i+1);
                            scanf("%s",nom_col);
                            add_column(data,nom_col);
                        }
                        for(int i = 0; i<nb_col;i++){

                            printf("\tRemplissage de la colonne %d\n", i+1);
                            for(int j = 0; j<nb_row;j++) {

                                printf("Saisir une valeur : \n");
                                scanf("%d",&val);
                                insert_value(data->col_tab[i],val);
                            }
                        }
                        printf("\tFin du remplissage\n");

                }
                break;

            case 2:
                printf("\t\tAffichage\n\n");
                printf("1. \tAfficher tout le CDataframe\n"
                       "2. \tAfficher une partie des lignes du CDataframe selon une limite fournie par l’utilisateur\n"
                       "3. \tAfficher une partie des colonnes du CDataframe selon une limite fournie par l’utilisateur\n");
                scanf("%d", &second_choice_menu);
                switch (second_choice_menu) {
                    case 1:
                        if (data == NULL)
                            printf("Aucune données");
                        else
                            print_database(data);

                        break;

                    case 2 :
                        printf("Sasir la borne inferieure : ");
                        scanf("%d",&inf);
                        printf("Sasir la borne superieure : ");
                        scanf("%d",&sup);
                        some_row(data,inf,sup);
                        break;

                    case 3:
                        printf("Sasir la borne inferieure : ");
                        scanf("%d",&inf);
                        printf("Sasir la borne superieure : ");
                        scanf("%d",&sup);
                        some_column(data,inf,sup);
                        break;
                }
                break;

            case 3:
                printf("\tOpérations usuelles\n\n");
                printf("1. \tAjouter une ligne de valeurs au CDataframe\n"
                       "2. \tSupprimer une ligne de valeurs du CDataframe\n"
                       "3. \tAjouter une colonne au CDataframe\n"
                       "4. \tSupprimer une colonne du CDataframe\n"
                       "5. \tRenommer le titre d’une colonne du CDataframe\n"
                       "6. \tVérifier l’existence d’une valeur (recherche) dans le CDataframe\n"
                       "7. \tAccéder/remplacer la valeur se trouvant dans une cellule du CDataframe en utilisant son numéro de ligne et de colonne\n"
                       "8. \tAfficher les noms des colonnes\n");
                scanf("%d", &second_choice_menu);
                switch (second_choice_menu) {
                    case 1 :

                        if (data->nb_col == 0)
                            printf("Aucune colonne trouvée, l'ajout n'a pas été effectué ");
                        else {
                            add_row_to_database(data);
                            }

                        break;

                    case 2 :
                        if (data->nb_row == 0) {
                            printf("Aucune ligne trouvée");
                            printf("Saisir la ligne à supprimer : \n");
                            scanf("%d", &val);
                        }
                        else {
                            database_delete_row(data, val);
                        }
                        break;

                    case 3:
                        printf("Veuillez saisir le nom de la colonne : \n");
                        scanf("%s", nom_col);
                        add_column(data, nom_col);
                        break;

                    case 4:
                        for (int i = 0; i < data->nb_col; i++) {
                            printf("[%d] %s\n", i, data->col_tab[i]->titre);
                        }
                        printf("Veuillez saisir le numéro de la colonne à effacer : \n");
                        scanf("%d",&nb_col);
                        delete_column_from_databse(data,nb_col);
                        break;

                    case 5:
                        for (int i = 0; i < data->nb_col; i++) {
                            printf("[%d] %s\n", i, data->col_tab[i]->titre);
                        }
                        printf("Veuillez saisir le numéro actuel de la colonne : \n");
                        scanf("%d",&nb_col);
                        printf("Veuillez saisir le nouveau nom de la colonne : ");
                        scanf("%s",new_col_name);
                        change_name_col(data,nb_col,new_col_name);
                        break;

                    case 6:
                        printf("Saisir la valeur à rechercher dans le tableau : \n");
                        scanf("%d",&val);
                        check_value_in_database(data, val);
                        break;

                    case 7:
                        printf("Veuillez saisir le numéro de la colonne de la valeur: \n");
                        scanf("%d",&nb_col);
                        printf("Veuillez saisir le numéro de la ligne de la valeur : ");
                        scanf("%d",&nb_row);
                        printf("Veuillez saisir la nouvelle valeur : \n");
                        scanf("%d",&val);
                        change_database_value(data,nb_col,nb_row,val);
                        break;

                    case 8:
                        print_name_column_database(data->col_tab, data->nb_col);

                }
                break;

            case 4:
                printf("\tAnalyse et statistiques\n\n");
                printf("1. \tAfficher le nombre de lignes\n"
                       "2. \tAfficher le nombre de colonnes\n"
                       "3. \tNombre de cellules contenant une valeur égale à x (x donné en paramètre)\n"
                       "4. \tNombre de cellules contenant une valeur supérieure à x (x donné en paramètre)\n"
                       "5. \tNombre de cellules contenant une valeur inférieure à x(x donné en paramètre)\n");
                scanf("%d", &second_choice_menu);
                switch (second_choice_menu) {
                    case 1 :
                        printf("Il y a %d ligne(s)",data->nb_row);
                        break;

                    case 2 :
                        printf("Il y a %d colonne(s)",data->nb_col);
                        break;

                    case 3 :
                        printf("Veuillez saisir une valeur : \n");
                        scanf("%d",&val);
                        if (nb_occ_in_database(data,val)!= 0)
                            printf("La valeur %d a été trouvée %d fois\n",val,nb_occ_in_database(data,val));
                        if (nb_occ_in_database(data,val)== 0)
                            printf("La valeur %d n'a pas été trouvée\n ",val);
                        break;

                    case 4:
                        printf("Veuillez saisir une valeur : \n");
                        scanf("%d",&val);
                        if (nb_occ_greater_in_database(data,val)>1)
                            printf("%d valeurs supérieures à %d ont été trouvées\n",nb_occ_greater_in_database(data,val),val);
                        else if (nb_occ_greater_in_database(data,val) == 1)
                            printf("%d valeur supérieure à %d à été trouvée\n",nb_occ_greater_in_database(data,val),val);
                        else if (nb_occ_greater_in_database(data,val) == 0)
                            printf("Aucune valeur supérieure à %d n'à été trouvée\n",val);
                        break;

                    case 5:
                        printf("Veuillez saisir une valeur : \n");
                        scanf("%d",&val);
                        if (nb_occ_lower_in_database(data,val)>1)
                            printf("%d valeurs inférieures à %d ont été trouvées\n",nb_occ_lower_in_database(data,val),val);
                        else if (nb_occ_lower_in_database(data,val)==1)
                            printf("%d valeur inférieure à %d à été trouvée\n",nb_occ_lower_in_database(data,val),val);
                        else if (nb_occ_lower_in_database(data,val)==0)
                            printf("Aucune valeur inférieure à %d n'à été trouvée\n",val);
                        break;
                }
                break;

            default : {
                printf("Valeur invalide");
                return 1;
            }

        }
        nb++;
    }
    return 0;
}

