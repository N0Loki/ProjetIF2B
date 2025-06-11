//
// Created by Julie on 29/05/2025.
//

#include "game.h"
#include "setup.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

extern void setup();
extern void gameStart();

const char* get_unicode_piece(TypePiece piece, Couleurs couleur) {
    if (couleur == Blanc) {
        switch (piece) {
            case Roi: return "♔";
            case Dame: return "♕";
            case Tour: return "♖";
            case Fou: return "♗";
            case Cavalier: return "♘";
            case Pion: return "♙";
            default: return " ";
        }
    } else if (couleur == Noir) {
        switch (piece) {
            case Roi: return "♚";
            case Dame: return "♛";
            case Tour: return "♜";
            case Fou: return "♝";
            case Cavalier: return "♞";
            case Pion: return "♟";
            default: return " ";
        }
    }
    return " ";
}

/**
 * Fonction affichant les couleurs sur le texte et le fond
 * @param texte Couleur choisie pour le texte
 * @param fond Couleur choisie pour le fond
 */
void setColor(Couleur texte, Couleur fond) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, fond * 16 + texte);
}

/**
 * Affiche les lettres de colonnes en haut et en bas du plateau
 * @param taille La taille du plateau (nb de colonnes)
 */
void afficherColonnes(int taille) {
    printf(" ");
    for (int x = 0; x < taille; ++x) {
        printf("  %c ", 'A' + x);
    }
    printf("\n");
}

void afficherPlateau(int taille, Case **board) {
    const Couleur fond_clair = GRIS_CLAIR;
    const Couleur fond_fonce = GRIS_FONCE;

    afficherColonnes(taille);

    for (int y = 0; y < taille; ++y) {

        printf("  +");
        for (int x = 0; x < taille; x++) {
            printf("----+");
        }
        printf("\n");

        printf("  |");
        for (int x = 0; x < taille; ++x) {
            Couleur fond = ((x + y) % 2 == 0) ? fond_clair : fond_fonce;
            Couleur texte = board[y][x].couleurPiece == Blanc ? WHITE :
                            board[y][x].couleurPiece == Noir ? BLACK : GRIS_CLAIR;

            setColor(texte, fond);
            const char* symbole = get_unicode_piece(board[y][x].contenu, board[y][x].couleurPiece);
            printf(" %-2s ", symbole);
            setColor(WHITE, BLACK);
            printf("|");
        }
        printf("\n");
    }

    printf("  +");
    for (int i = 0; i < taille; i++) {
        printf("----+");
    }
    printf("\n");

    afficherColonnes(taille);
}

/**
 * Vide le plateau
 * @param taille La taille du plateau (nb de colonnes)
 * @param board Le plateau
 */
void gameEnd(int taille, Case **board) {
    for (int i = 0; i < taille; i++) {
        free(board[i]);
    }
    free(board);

    printf("Merci d'avoir joué !");
}


void game() {
    int joueur, taille, modeJeu;
    Case **board;
    setup(&joueur, &taille, &modeJeu, &board);
    afficherPlateau(taille, board);
    gameStart(joueur, taille, board);




    gameEnd(taille, board);
}