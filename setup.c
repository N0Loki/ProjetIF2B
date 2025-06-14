#include "setup.h"
#include"game.h"


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#ifdef _WIN32
#include <windows.h>
#endif


/**
 * Active le support de l'UTF-8 dans la console Windows.
 * Ne fait rien sur les autres systèmes.
 */
void include_uni() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        system("chcp 65001 > nul");
    #endif
}


/**
 * Choisit aléatoirement quel joueur commence.
 *
 * @return 1 pour le joueur blanc, 2 pour le joueur noir.
 */
int choix_joueur() {
    srand(time(NULL));
    int player = rand() % 2 + 1;
    return player;
}


/**
 * Demande à l'utilisateur une taille de plateau entre 6 et 12.
 *
 * @return La taille choisie par l'utilisateur.
 */
int choix_taille() {
    int size = 0;
    char answer[10];
    do {
        printf("Quelle sont les dimensions de l'échiquier, de 6x6 à 12x12 ? [6,7,8,9,10,11,12]\n");
        scanf("%s", &answer);
        size = strtol(answer, NULL, 10);
        if (size < 6 || size > 12) {
            printf("Taille non reconnue !\n");
        }
    }   while (size < 6 || size > 12);
    return size;
}


/**
 * Demande à l'utilisateur de choisir le mode de jeu.
 *
 * @return 1 pour le mode Conquête, 2 pour le mode Connecte.
 */
int choix_mode() {
    int mode;
    char answer[10];
    do {
        printf("A quel mode de jeu voulez-vous jouer ? [Conquête : 1, Connecte : 2]\n");
        scanf("%s", &answer);
        mode = strtol(answer, NULL, 10);
        if (mode != 1 && mode !=2) {
            printf("Mode non reconnu!\n");
        }
    }   while (mode != 1 && mode !=2);
    return mode;
}


/**
 * Alloue dynamiquement un plateau carré de la taille spécifiée et initialise les cases.
 *
 * @param size La taille du plateau (nombre de lignes et colonnes).
 * @return Un tableau 2D de pointeurs vers les structures Case initialisées.
 */
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
            board[i][j].contenu = VIDE;
            board[i][j].captureeParPiece = VIDE;
            board[i][j].couleurPiece = NONE;
            board[i][j].captured = NONE;
        }
    }

    return board;
}

/**
 * Initialise tous les paramètres de la partie.
 * Active l'UTF-8, choisit le joueur aléatoire, demande la taille et le mode,
 * et crée le plateau de jeu.
 *
 * @param joueur Pointeur vers l'entier qui contiendra le joueur qui commence (1 ou 2).
 * @param taille Pointeur vers l'entier qui contiendra la taille du plateau.
 * @param modeJeu Pointeur vers l'entier contenant le mode de jeu choisi.
 * @param board Pointeur vers le tableau 2D de cases du plateau à initialiser.
 */
void setup(int* joueur, int* taille, int* modeJeu, Case ***board) {
    *joueur = choix_joueur();
    *taille = choix_taille();
    *modeJeu = choix_mode();
    *board = create_board(*taille);
    printf("\n Début du jeu !\n");
}