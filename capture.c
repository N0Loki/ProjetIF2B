#include "capture.h"
#include "game.h"

#include <stdio.h>


/**
 * Vérifie si une position est dans les limites du plateau.
 *
 * @param x Colonne
 * @param y Ligne
 * @param taille Taille du plateau
 * @return 1 si valide, 0 sinon
 */
int estDansLesLimites(int x, int y, int taille) {
    return x >= 0 && x < taille && y >= 0 && y < taille;
}


/**
 * Capture avec un pion.
 *
 * @param joueur Couleur du joueur (BLANC ou NOIR)
 * @param x Coordonnée ligne
 * @param y Coordonnée colonne
 * @param taille Taille du plateau
 * @param piece Type de la pièce (PION)
 * @param board Plateau de jeu
 * @return 1 si capture effectuée, 0 sinon
 */
int capturePion(int joueur, int x, int y, int taille, TypePiece piece, Case **board) {
    int direction = (joueur == BLANC) ? -1 : 1;
    int dy[] = {-1, 1};
    int captureEffectuee = 0;

    for (int i = 0; i < 2; i++) {
        int nx = x + direction;
        int ny = y + dy[i];
        if (estDansLesLimites(nx, ny, taille)) {
            if (board[nx][ny].contenu == VIDE) {
                board[x][y].contenu = piece;
                board[nx][ny].captured = joueur;
                board[nx][ny].captureeParPiece = piece;
                captureEffectuee = 1;
            }
        }
    }
    return captureEffectuee;
}

/**
 * Capture avec un cavalier.
 *
 * @param joueur Couleur du joueur (BLANC ou NOIR)
 * @param x Coordonnée ligne
 * @param y Coordonnée colonne
 * @param taille Taille du plateau
 * @param piece Type de la pièce (CAVALIER)
 * @param board Plateau de jeu
 * @return 1 si capture effectuée, 0 sinon
 */
int captureCavalier(int joueur, int x, int y, int taille, TypePiece piece, Case **board) {
    int captureEffectuee = 0;
    int deplacements[8][2] = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };

    for (int i = 0; i < 8; i++) {
        int nx = x + deplacements[i][0];
        int ny = y + deplacements[i][1];
        if (estDansLesLimites(nx, ny, taille)) {
            if (board[nx][ny].contenu == VIDE && board[nx][ny].couleurPiece != joueur) {
                board[nx][ny].captured = joueur;
                board[nx][ny].captureeParPiece = piece;
                captureEffectuee = 1;
            }
        }

    }
    return captureEffectuee;
}

/**
 * Capture avec un fou.
 *
 * @param joueur Couleur du joueur (BLANC ou NOIR)
 * @param x Coordonnée ligne
 * @param y Coordonnée colonne
 * @param taille Taille du plateau
 * @param piece Type de la pièce
 * @param board Plateau de jeu
 * @return 1 si capture effectuée, 0 sinon
 */
int captureFou(int joueur, int x, int y, int taille, TypePiece piece, Case **board) {
    int captureEffectuee = 0;
    int directions[4][2] = {{1,1}, {1,-1}, {-1,1}, {-1,-1}};

    for (int d = 0; d < 4; d++) {
        int dx = directions[d][0];
        int dy = directions[d][1];
        int nx = x + dx;
        int ny = y + dy;

        while (estDansLesLimites(nx, ny, taille) && board[nx][ny].contenu == VIDE) {
            board[nx][ny].captured = joueur;
            board[nx][ny].captureeParPiece = piece;
            captureEffectuee = 1;

            nx += dx;
            ny += dy;
        }
    }
    return captureEffectuee;
}

/**
 * Capture avec une tour.
 *
 * @param joueur Couleur du joueur (BLANC ou NOIR)
 * @param x Coordonnée ligne
 * @param y Coordonnée colonne
 * @param taille Taille du plateau
 * @param piece Type de la pièce
 * @param board Plateau de jeu
 * @return 1 si capture effectuée, 0 sinon
 */
int captureTour(int joueur, int x, int y, int taille, TypePiece piece, Case **board) {
    int captureEffectuee = 0;
    int directions[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};

    for (int d = 0; d < 4; d++) {
        int dx = directions[d][0];
        int dy = directions[d][1];
        int nx = x + dx;
        int ny = y + dy;

        while (estDansLesLimites(nx, ny, taille) && board[nx][ny].contenu == VIDE) {
            board[nx][ny].captured = joueur;
            board[nx][ny].captureeParPiece = piece;
            captureEffectuee = 1;

            nx += dx;
            ny += dy;
        }
    }
    return captureEffectuee;
}

/**
 * Capture avec une dame (combinaison fou + tour).
 *
 * @param joueur Couleur du joueur (BLANC ou NOIR)
 * @param x Coordonnée ligne
 * @param y Coordonnée colonne
 * @param taille Taille du plateau
 * @param piece Type de la pièce (DAME)
 * @param board Plateau de jeu
 * @return 1 si capture effectuée, 0 sinon
 */
int captureDame(int joueur, int x, int y, int taille, TypePiece piece, Case **board) {
    int captFou = captureFou(joueur, x, y, taille, piece, board);
    int captTour = captureTour(joueur, x, y, taille, piece, board);
    return captFou || captTour;
}

/**
 * Capture avec un roi.
 *
 * @param joueur Couleur du joueur (BLANC ou NOIR)
 * @param x Coordonnée ligne
 * @param y Coordonnée colonne
 * @param taille Taille du plateau
 * @param piece Type de la pièce (ROI)
 * @param board Plateau de jeu
 * @return 1 si capture effectuée, 0 sinon
 */
int captureRoi(int joueur, int x, int y, int taille, TypePiece piece, Case **board) {
    int captureEffectuee = 0;
    int directions[8][2] = {
        {1,0}, {-1,0}, {0,1}, {0,-1},
        {1,1}, {1,-1}, {-1,1}, {-1,-1}
    };

    for (int i = 0; i < 8; i++) {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];
        if (estDansLesLimites(nx, ny, taille)) {
            if (board[nx][ny].contenu == VIDE && board[nx][ny].couleurPiece != joueur) {
                board[nx][ny].captured = joueur;
                board[nx][ny].captureeParPiece = piece;
                captureEffectuee = 1;
            }
        }
    }
    return captureEffectuee;
}


/**
 * Détermine quelle fonction de capture appeler selon la pièce.
 *
 * @param joueur Couleur du joueur (BLANC ou NOIR)
 * @param piece Type de pièce
 * @param x Coordonnée ligne
 * @param y Coordonnée colonne
 * @param taille Taille du plateau
 * @param board Plateau de jeu
 * @return 1 si capture effectuée, 0 sinon
 */
int capturerSelonPiece(int joueur, TypePiece piece, int x, int y, int taille, Case **board) {
    int result = 0;
    switch (piece) {
        case PION:
            result = capturePion(joueur, x, y, taille, piece, board);
            break;
        case CAVALIER:
            result = captureCavalier(joueur, x, y, taille, piece, board);
        break;
        case FOU:
            result = captureFou(joueur, x, y, taille, piece, board);
        break;
        case TOUR:
            result = captureTour(joueur, x, y, taille, piece, board);
        break;
        case DAME:
            result = captureDame(joueur, x, y, taille, piece, board);
        break;
        case ROI:
            result = captureRoi(joueur, x, y, taille, piece, board);
        break;
        default:
            printf("Type de pièce inconnu pour capture.\n");
            return 0;
    }
    board[x][y].captured = joueur;
    board[x][y].couleurPiece = joueur;
    board[x][y].contenu = piece;
    return result;
}



