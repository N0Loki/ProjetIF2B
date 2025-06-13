#include "game.h"
#include "pose.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>

extern void createSave(int joueur, int taille, int modeJeu, int totalPieces[2][7], Case **board, char fileName[]);
extern int capturerSelonPiece(int joueur, TypePiece piece, int x, int y, int taille, Case **board);


/**
 * Vérifie s'il reste des pièces à poser pour un joueur donné
 *
 * @param joueur Couleur du joueur (BLANC ou NOIR)
 * @return 1 s'il reste des pièces, 0 sinon
 */
int reste_piece(Couleurs joueur, int totalPieces[3][7]) {
    if (joueur != BLANC && joueur != NOIR) {
        fprintf(stderr, "Erreur : couleur invalide dans reste_piece\n");
        return 0;
    }

    for (int i = 1; i <= 6; i++) {
        if (totalPieces[joueur][i] > 0) {
            return 1;
        }
    }
    return 0;
}


/**
 * Affiche les pièces restantes du joueur.
 *
 * @param joueur Le joueur actif (BLANC ou NOIR).
 * @param totalPieces Tableau des pièces restantes [3][7] pour chaque joueur :
 *                    totalPieces[joueur][typePiece] donne le nombre restant.
 */
void afficher_Pieces_restantes(int joueur, int totalPieces[3][7]) {
    printf("____________________\n");
    printf("| %-12s | %2d |\n", "Pion ♙", totalPieces[joueur][1]);
    printf("| %-9s | %2d |\n", "Cavalier ♘", totalPieces[joueur][2]);
    printf("| %-12s | %2d |\n", "Fou ♗", totalPieces[joueur][3]);
    printf("| %-12s | %2d |\n", "Tour ♖", totalPieces[joueur][4]);
    printf("| %-12s | %2d |\n", "Dame ♕", totalPieces[joueur][5]);
    printf("| %-12s | %2d |\n", "Roi ♔", totalPieces[joueur][6]);
    printf("____________________\n");
}

/**
 * Fonction convertissant une chaîne de caractères en minuscules
 *
 * @param str Chaîne à convertir
 */
void toLowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = (char)tolower(str[i]);
    }
}

/**
 * Fonction convertissant une lettre représentant une colonne en indice
 *
 * @param lettre Lettre représentant une colonne
 * @return Indice correspondant
 */
int transLettre(char lettre) {
    if (lettre >= 'a' && lettre <= 'z') {
        return lettre - 'a';
    } else if (lettre >= 'A' && lettre <= 'Z') {
        return lettre - 'A';
    }
    return -1;
}

/**
 * Retourne le nom textuel d'une pièce d'échecs selon son type.
 *
 * Cette fonction permet d'afficher des messages plus lisibles pour les joueurs,
 * en convertissant une valeur de l'énumération TypePiece en une chaîne de caractères.
 *
 * @param piece Le type de pièce (PION, CAVALIER, FOU, TOUR, DAME, ROI)
 * @return const char* Le nom de la pièce en français. "Inconnue" si le type est invalide.
 */
const char* nomPiece(TypePiece piece) {
    switch (piece) {
        case PION:     return "Pion";
        case CAVALIER: return "Cavalier";
        case FOU:      return "Fou";
        case TOUR:     return "Tour";
        case DAME:     return "Dame";
        case ROI:      return "Roi";
        default:       return "Inconnue";
    }
}


/**
 * Tente de poser une pièce sur une case vide du plateau, selon les règles du mode de jeu.
 *
 * En mode Conquête (1) : la pièce peut être posée sur toute case vide.
 * En mode Connecte (2) : la pièce doit être posée sur une case vide, mais capturée selon une hiérarchie stricte.
 *
 * @param joueur Joueur actuel (BLANC ou NOIR)
 * @param piece Type de pièce à poser
 * @param x Ligne cible (indexée à 0)
 * @param y Colonne cible (indexée à 0)
 * @param taille Taille du plateau
 * @param modeJeu Mode de jeu (1 = Conquête, 2 = Connecté)
 * @param board Plateau de jeu
 * @return 1 si la pièce a été posée avec succès et les captures appliquées, 0 sinon
 */
int poser_et_valider_piece(int joueur, TypePiece piece, int x, int y, int taille, int modeJeu, Case **board) {
    if (board[x][y].contenu != VIDE) {
        printf("Erreur : la case est déjà occupée.\n");
        return 0;
    }

    if (modeJeu == 2) {
        int condition_valide = 0;
        TypePiece type_necessaire = PION;

        switch (piece) {
            case PION:
                if (board[x][y].contenu == VIDE) {
                    condition_valide = 1;
                }
                break;
            case CAVALIER:
                type_necessaire = PION;
                break;
            case FOU:
                type_necessaire = CAVALIER;
                break;
            case TOUR:
                type_necessaire = FOU;
                break;
            case DAME:
                type_necessaire = TOUR;
                break;
            case ROI:
                type_necessaire = DAME;
                break;
            default:
                break;
        }

        if (piece != PION) {
            if (board[x][y].contenu == VIDE && board[x][y].captureeParPiece == type_necessaire && board[x][y].captured == joueur) {
                condition_valide = 1;
            } else {
                printf("Erreur : le %s ne peut être posé que sur une case vide capturée par un %s de votre couleur.\n",
                       nomPiece(piece), nomPiece(type_necessaire));
                return 0;
            }
        }

        if (condition_valide) {
            capturerSelonPiece(joueur, piece, x, y, taille, board);
            afficherPlateau(taille, board);
                return 1;
            }
    }
    if (board[x][y].contenu == VIDE) {
        capturerSelonPiece(joueur, piece, x, y, taille, board);
        afficherPlateau(taille, board);
        return 1;
    }
    printf("Erreur : la capture échoue pour le %s en position %c%d.\n", nomPiece(piece), 'a' + y, x + 1);
    return 0;
}

/**
 * Demande au joueur de choisir une pièce parmi celles qu'il possède encore.
 *
 * @param joueur Couleur du joueur (BLANC ou NOIR)
 * @param totalPieces Tableau des pièces restantes pour chaque joueur [3][7]
 * @return TypePiece choisie
 */
TypePiece demanderPiece(int joueur, int totalPieces[3][7]) {
    char reponsePiece[10];
    TypePiece piece = VIDE;

    while (1) {
        afficher_Pieces_restantes(joueur, totalPieces);
        printf("\nQuelle pièce voulez-vous poser ? [pion,cavalier,fou,tour,dame,roi]\n");
        scanf(" %9s", reponsePiece);
        toLowercase(reponsePiece);

        if (strcmp(reponsePiece, "pion") == 0) piece = PION;
        else if (strcmp(reponsePiece, "fou") == 0) piece = FOU;
        else if (strcmp(reponsePiece, "cavalier") == 0) piece = CAVALIER;
        else if (strcmp(reponsePiece, "tour") == 0) piece = TOUR;
        else if (strcmp(reponsePiece, "dame") == 0) piece = DAME;
        else if (strcmp(reponsePiece, "roi") == 0) piece = ROI;
        else {
            printf("\nLa pièce %s n'existe pas !\n", reponsePiece);
            continue;
        }

        if (totalPieces[joueur][piece] > 0) {
            return piece;
        } else {
            printf("\nVous n'avez plus de %s.\n", reponsePiece);
        }
    }
}


/**
 * Demande au joueur une position valide sur le plateau
 *
 * @param tailleEchiquier Taille du plateau
 * @param[out] x Coordonnée ligne (indexée à 0)
 * @param[out] y Coordonnée colonne (indexée à 0)
 */
void demanderPosition(int tailleEchiquier, int *x, int *y) {
    char lettreColonne;
    int ligne;

    while (1) {
        printf("\nSur quelle case ? (format: lettre chiffre, exemple : f6, g7, etc.)\n");
        scanf(" %c%d", &lettreColonne, &ligne);
        *y = transLettre(lettreColonne);
        *x = ligne - 1;

        if (*x >= 0 && *x < tailleEchiquier && *y >= 0 && *y < tailleEchiquier)
            break;
        else
            printf("Coordonnées invalides, réessayez.\n");
    }
}


/**
 * Gère le tour d’un joueur pour poser une pièce sur le plateau.
 * Demande la pièce à poser, la position où la poser, tente de poser la pièce,
 * met à jour le nombre de pièces restantes et change de joueur si la pose est réussie.
 * Affiche le score et termine la partie si le roi est posé en mode Connecté.
 *
 * @param joueur Couleur du joueur actuel (BLANC ou NOIR)
 * @param taille Taille du plateau de jeu
 * @param modeJeu Mode de jeu (1 = Conquête, 2 = Connecté)
 * @param totalPieces Tableau contenant les pièces restantes pour chaque joueur [3][7]
 * @param board Plateau de jeu (tableau 2D de cases)
 * @return Couleur du joueur suivant (BLANC ou NOIR)
 */
int tour_joueur_poser_piece(int joueur, int taille, int modeJeu, int totalPieces[3][7], Case **board) {
    TypePiece piece = demanderPiece(joueur, totalPieces);
    int x, y;

    demanderPosition(taille, &x, &y);

    if (poser_et_valider_piece(joueur, piece, x, y, taille, modeJeu, board)) {
        totalPieces[joueur][piece]--;

        if (piece == ROI && modeJeu == 2) {
            printf("Le roi a été posé. La partie est terminée pour vous !\n");
        }

        joueur = (joueur == BLANC) ? NOIR : BLANC;
        printf("Au tour des %s.\n", joueur == BLANC ? "Blancs" : "Noirs");
    }
    return joueur;
}