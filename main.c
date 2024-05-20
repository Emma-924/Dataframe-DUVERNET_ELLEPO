#include <stdio.h>
#include "Dataframe.h"


int main() {
    

    CDATAFRAME *data;
    int choice_menu=0;

    printf("\nBonjour,"
           "\nVeuillez chosir une action à effectuer");
    while (choice_menu!=5) {
        printf("\n");
        printf( "1- Alimentation\n"
                "2- Affichage\n"
                "3- Opérations usuelles\n"
                "4- Analyse et statistiques\n"
                "5- Quitter\n");
        scanf("%d", &choice_menu);

        switch (choice_menu) {
            case 1:
                alimentation(&data);
                break;

            case 2:
                affichage(&data);
                break;

            case 3:
                operations_usuelles(&data);
                break;

            case 4:
                analyse_statistiques(&data);
                break;

            case 5 :
                // permet de quitter
                printf("Au revoir !");
                return 1;

            default : {
                printf("Valeur invalide");
            }

        }
    }
    return 0;

}
