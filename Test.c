// ----- Importation des libraires -----

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ----- Définitions globales -----

// ----- Déclarations prototypes fonctions -----

//Création de l'échiquier

/*
 *int size_Enter() {
    int size;
    char answer;
    do {
        printf("\nQuelle taille allant de 6x6 a 12x12 fera le plateau ? [6,7,8,9,10,11,12]\n");
        scanf("%s", &answer);
        size = strtol(&answer, NULL, 10);
    } while (!(size >= 6 || size <= 12));
    return size;
}
*/

void board() {
    int size;
    typedef struct {
        int color;
        int captured = 3;
        int contours;
    }Case;

    Case board[size][size];
    for (int i = 0; i < size+1; i++) {
        board[i][1].contours = i+1;
        board[1][i].contours = i+1;
    }
    printf("%d",board[2][2].color);
}



//Return white, if 1 then is White, if 0 then is Black.
int* player_Choice(int* White) {
    srand(time(NULL));
    White+=rand()%1;
    return White;
}



void random_Bullshit_In_Test(){



}



//Se lance au début du jeu
void game() {





}