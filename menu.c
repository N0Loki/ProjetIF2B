/* Created by Julie on 06/05/2025. */

#include "menu.h"

#include <stdio.h>
#include <stdlib.h>

extern void game();
extern void saves();

//Start the program, allow users to choose and verify cases

int main() {
    int choix;
    char answer;
    do {
        printf("\n");
        printf("┌───────────────────────────────────────────────┐\n");
        printf("│Actions :                                      │\n");
        printf("├───────────────────────────────────────────────┤\n");
        printf("│[1] - Nouvelle partie                          │\n");
        printf("│[2] - Charger sauvegarde                       │\n");
        printf("│[3] - Quitter                                  │\n");
        printf("└───────────────────────────────────────────────┘\n");
        printf("\nQue voulez vous faire ? [1/2/3]\n");
        scanf("%s", &answer);
        choix = strtol(&answer, NULL, 10);
        switch (choix){
            case 1:
                game();
                break;
            case 2:
                saves();
                break;
            case 3:
                break;
            default:
                printf("\nMauvais nombre saisi\n");
        }
    }while(choix !=3);
}
