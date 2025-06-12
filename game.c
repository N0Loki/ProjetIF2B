#include "game.h"
#include "saves.h"
#include "pose.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

extern void setup();
extern Case** loadSave();
extern void gameTurn();


/**
 * Retourne le symbole Unicode correspondant à une pièce d'échecs
 * en fonction de son type et de sa couleur.
 *
 * @param piece Le type de la pièce
 * @param couleur La couleur de la pièce
 * @return Une chaîne représentant le symbole Unicode
 */
const char* get_unicode_piece(TypePiece piece, Couleurs couleur) {
    if (couleur == BLANC) {
        switch (piece) {
            case ROI: return "♔";
            case DAME: return "♕";
            case TOUR: return "♖";
            case FOU: return "♗";
            case CAVALIER: return "♘";
            case PION: return "♙";
            default: return " ";
        }
    }
    if (couleur == NOIR) {
        switch (piece) {
            case ROI: return "♚";
            case DAME: return "♛";
            case TOUR: return "♜";
            case FOU: return "♝";
            case CAVALIER: return "♞";
            case PION: return "♟";
            default: return " ";
        }
    }
    return " ";
}

/**
 * Fonction affichant les couleurs sur le texte et le fond
 *
 * @param texte Couleur choisie pour le texte
 * @param fond Couleur choisie pour le fond
 */
void setColor(Couleur texte, Couleur fond) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, fond * 16 + texte);
}


/**
 * Affiche les lettres de colonnes en haut et en bas du plateau
 *
 * @param taille La taille du plateau (nb de colonnes)
 */
void afficherColonnes(int taille) {
    printf(" ");
    for (int x = 0; x < taille; ++x) {
        printf("   %c ", 'A' + x);
    }
    printf("\n");
}


/**
 * Affiche l’état actuel du plateau avec les pièces et les couleurs de fond.
 *
 * @param taille La taille du plateau
 * @param board Le plateau de jeu (Matrice 2D dynamique de Case)
 */
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


        printf("%2d|", y + 1);

        for (int x = 0; x < taille; ++x) {
            Couleur fond;

            if (board[y][x].captured == BLANC) {
                fond = BLEU_CLAIR;
            }

            else if (board[y][x].captured == NOIR) {
                fond = ROUGE_FONCE;
            }
            else {

                fond = ((x + y) % 2 == 0) ? fond_clair : fond_fonce;
            }

            Couleur texte;
            if (board[y][x].couleurPiece == BLANC)
                texte = WHITE;
            else if (board[y][x].couleurPiece == NOIR)
                texte = BLACK;
            else
                texte = GRIS_CLAIR;

            setColor(texte, fond);

            const char* symbole = get_unicode_piece(board[y][x].contenu, board[y][x].couleurPiece);
            printf(" %-2s ", symbole);

            setColor(WHITE, BLACK);
            printf("|");
        }

        printf("%2d\n", y + 1);
    }

    printf("  +");
    for (int i = 0; i < taille; i++) {
        printf("----+");
    }
    printf("\n");

    afficherColonnes(taille);
}


/**
 * Fonction calculant et affichant les scores des deux joueurs
 *
 * @param taille Taille du plateau
 * @param board Plateau de jeu
 */
void scorer(int taille, Case **board) {
    int scoreBlanc = 0;
    int scoreNoir = 0;

    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            if (board[i][j].captured != NONE) {
                if (board[i][j].couleurPiece == BLANC) {
                    scoreBlanc++;
                } else if (board[i][j].couleurPiece == NOIR) {
                    scoreNoir++;
                }
            }
        }
    }
    printf("Score des Blancs : (%d).\n", scoreBlanc);
    printf("Score des Noirs  : (%d).\n", scoreNoir);
}


/**
 * Vide le plateau
 *
 * @param taille La taille du plateau (nb de colonnes)
 * @param board Le plateau
 */
void gameEnd(int taille, Case **board) {
    for (int i = 0; i < taille; i++) {
        free(board[i]);
        board[i] = NULL;
    }
    free(board);
    board = NULL;

    printf("Merci d'avoir joué !");
}


/**
 * Gère le tour complet d’un joueur : choix d'action, pose de pièce, abandon ou sauvegarde.
 *
 * @param joueur Le joueur courant (BLANC ou NOIR)
 * @param taille La taille du plateau
 * @param modeJeu Le mode de jeu sélectionné
 * @param totalPieces Tableau contenant les pièces restantes pour chaque joueur
 * @param board Plateau de jeu (Matrice 2D dynamique)
 */
void gameTurn(int joueur, int taille, int modeJeu, int totalPieces[3][7], Case **board) {
    int choix = 0;
    char answer;

    while (1) {
        printf("\nPhase de jeu\n");
        printf("Que voulez-vous faire joueur %s ?\n", joueur == 1 ? "Blanc" : "Noir");

        if (!reste_piece(joueur, totalPieces)) {
            printf("Joueur %s : toutes vos pièces sont posées sur l'échiquier\n", joueur == BLANC ? "Blanc" : "Noir");
            scorer(taille, board);
        }

        printf("\n");
        printf("\t┌───────────────────────────────────────────────┐\n");
        printf("\t│Actions :                                      │\n");
        printf("\t├───────────────────────────────────────────────┤\n");
        if (reste_piece(joueur, totalPieces)) {
            printf("\t│[1] - Poser une pièce                          │\n");
        }
        printf("\t│[2] - Abandonner                               │\n");
        printf("\t│[3] - Sauvegarder la partie                    │\n");
        printf("\t└───────────────────────────────────────────────┘\n");
        printf("\n\tQue voulez vous faire ? [1/2/3]\n");

        scanf(" %c", &answer);
        choix = strtol(&answer, NULL, 10);

        switch (choix) {
            case 1:
                if (reste_piece(joueur, totalPieces)) {
                    joueur = tour_joueur_poser_piece(joueur, taille, modeJeu, totalPieces, board);
                    afficherPlateau(taille, board);
                } else {
                    printf("\nVous n'avez plus de pièces à poser !\n");
                }
                break;

            case 2:
                gameEnd(taille, board);
                return;

            case 3:
                char fileName[100];
            printf("Entrez un nom pour votre sauvegarde (ex : partie1.txt) : ");
            scanf("%99s", fileName);

            createSave(joueur, taille, modeJeu, totalPieces, board, fileName);
            gameEnd(taille, board);
                return;;

            default:
                printf("\nMauvais nombre saisi\n");
        }
    }
}


/**
 * Lance une nouvelle partie ou charge une sauvegarde selon le choix du menu.
 *
 * @param menu 1 pour nouvelle partie, 2 pour chargement de sauvegarde
 */
void game(int menu) {
    int joueur, taille, modeJeu;
    int totalPieces[3][7] = {
        {0,0, 0, 0, 0, 0, 0}, // NONE
        {1,8, 2, 2, 2, 1, 1}, // BLANC
        {1,8, 2, 2, 2, 1, 1}  // NOIR
    };
    Case **board;

    if (menu == 1) {
        setup(&joueur, &taille, &modeJeu, &board);
    } else {
        char nomFichier[100];
        printf("Entrez le nom du fichier de sauvegarde (ex : save1.txt) : ");
        scanf("%s", nomFichier);

        board = loadSave(&joueur, &taille, &modeJeu, totalPieces, nomFichier);
        if (board == NULL) {
            fprintf(stderr, "Échec du chargement. Fin du jeu.\n");
            return;
        }
    }
    afficherPlateau(taille, board);
    gameTurn(joueur, taille, modeJeu, totalPieces, board);
    scorer(taille, board);
    gameEnd(taille, board);
}