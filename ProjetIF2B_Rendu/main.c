#include "main.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * Fonction principale du programme.
 * Affiche un menu avec plusieurs options :
 * - Démarrer une nouvelle partie
 * - Charger une sauvegarde
 * - Quitter le programme
 *
 * La fonction boucle tant que l'utilisateur ne choisit pas de quitter (option 3).
 */
int main() {
    int choix;
    char answer;
    include_uni();
    do {
        printf("\n");
        printf("\t┌───────────────────────────────────────────────┐\n");
        printf("\t│Menu :                                         │\n");
        printf("\t├───────────────────────────────────────────────┤\n");
        printf("\t│[1] - Nouvelle partie                          │\n");
        printf("\t│[2] - Charger sauvegarde                       │\n");
        printf("\t│[3] - Quitter                                  │\n");
        printf("\t└───────────────────────────────────────────────┘\n");
        printf("\n\tQue voulez vous faire ? [1/2/3]\n");
        scanf("%s", &answer);
        choix = strtol(&answer, NULL, 10);
        switch (choix){
            case 1:
                game(choix);
                break;
            case 2:;
                game(choix);
                break;
            case 3:
                printf("\n\t A une prochaine fois !\n");
                break;
            default:
                printf("\nMauvais nombre saisi\n");
        }
    }while(choix !=3);
}
