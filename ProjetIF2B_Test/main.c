/* Created by Julie on 06/05/2025. */

#include "main.h"

#include <stdio.h>
#include <stdlib.h>

extern void game();
extern void saves();
extern void include_uni();
//Start the program, allow users to choose and verify cases

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
                game();
                break;
            case 2:
                int save_mode = 1;
                saves(save_mode);
                break;
            case 3:
                break;
            default:
                printf("\nMauvais nombre saisi\n");
        }
    }while(choix !=3);
}
