#include "game.h"
#include "setup.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int reste_Piece (int couleur) {
    for (int i = 1 ; i <= 6 ; i++) {
        if (totalPieces[couleur][i] > 0) {
            return 1 ;
        } // il reste des pièces à placer
    }
    return 0;
}


void scorer(int taille, Case **board) {
    int scoreBlanc = 0; // blanc <=> color = 1
    int scoreNoir = 0; // noir <=> color = 2

    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            if (board[i][j].captured != 0) {
                if (board[i][j].couleurPiece == 1) {
                    scoreBlanc++ ;
                } else if (board[i][j].couleurPiece == 2)  {
                    scoreNoir++ ;
                }
            }
        }
    }
    printf("Score des Blancs : (%d).\n", scoreBlanc);
    printf("Score des Noirs  : (%d).\n", scoreNoir);
}



/**
 * Fonction vérifiant si une position est dans les limites du plateau
 * @param x Colonne
 * @param y Ligne
 * @param taille Taille du plateau
 * @return 1 si valide, 0 sinon
 */
int estDansLesLimites(int x, int y, int taille) {
    return x >= 0 && x < taille && y >= 0 && y < taille;
}

/**
 * Fonction permettant de convertir une lettre majuscule en indice de colonne
 * @param lettre Lettre majuscule représentant la colonne (ex: 'A')
 * @return Indice de colonne (ex: 0 pour 'A')
 */
int lettreEnIndice(char lettre) {
    return toupper(lettre) - 'A';
}

/**
 * Fonction vérifiant si une case est vide
 * @param c Case à vérifier
 * @return 1 si vide, 0 sinon
 */
int estVide(Case c) {
    return c.contenu == Vide;
}

/**
 * Fonction permettant à un joueur de placer une pièce sur le plateau
 * @param joueur Joueur actuel (0 ou 1)
 * @param taille Taille du plateau
 * @param board Plateau de jeu
 */
void gameStart(int joueur, int taille, Case **board) {
    int choix;
    char answer;

    do {
        printf("\nPhase de jeu\n");
        printf("Que voulez-vous faire joueur %s ?\n", joueur == 0 ? "Blanc" : "Noir");
        if (reste_Piece(joueur) == 0) {
            printf("Joueur %s : toutes vos pièces sont posées sur l'échiquier\n", joueur == 0 ? "Blanc" : "Noir");
            scorer(taille, board);
        }
        else {
            do {
                printf("\n");
                printf("\t┌───────────────────────────────────────────────┐\n");
                printf("\t│Actions :                                      │\n");
                printf("\t├───────────────────────────────────────────────┤\n");
                printf("\t│[1] - Poser une pièce                          │\n");
                printf("\t│[2] - Abandonner                               │\n");
                printf("\t│[3] - Sauvegarder la partie                    │\n");
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
            }
        }
}
