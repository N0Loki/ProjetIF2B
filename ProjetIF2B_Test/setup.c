
#include "setup.h"


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Pour importer l'unicode
#ifdef _WIN32
#include <windows.h>
#endif




void include_uni() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8); // Nécessite <windows.h>
        system("chcp 65001 > nul"); // Active UTF-8 dans la console Windows
    #endif
}

//return a flag : 0 if black, 1 if white
int choix_joueur() {
    srand(time(NULL));
    int player = rand() % 1;
    return player;
}

//Renvoie une valeur de côté utilisée dans le reste du programme
int choix_taille() {
    int size = 0;
    do {
        printf("Quelle sont les dimensions de l'échiquier, de 6x6 à 12x12 ? [6,7,8,9,10,11,12]\n");
        scanf("%d", &size);
        if (size < 6 || size > 12) {
            printf("Taille non reconnue !\n");
        }
    }   while (size < 6 || size > 12);
    return size;
}

int choix_mode() {
    int mode = 0;
    do {
        printf(" A quel mode de jeu voulez-vous jouer ? [Conquête : 0, Connecte : 1]\n");
        scanf("%d", &mode);
        if (mode != 0 && mode !=1) {
            printf("Mode non reconnu!\n");
        }
    }   while (mode != 0 && mode !=1);
    return mode;
}

Case** create_board(int size) {

    Case** board  = malloc(sizeof(Case*) * size);
    if (!board) {
        printf("Erreur d'allocation de lignes\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        board[i] = malloc(sizeof(Case) * size);
        if (!board[i]) {
            printf("Erreur d'allocation de colonnes\n");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j].contenu = Vide;
            board[i][j].couleurPiece = None;
            board[i][j].captured = None;
        }
    }

    return board;
}


void setup(int* joueur, int* taille, int* modeJeu, Case ***board) {
    include_uni();
    *joueur = choix_joueur();
    *taille = choix_taille();
    *modeJeu = choix_mode();
    *board = create_board(*taille);
}