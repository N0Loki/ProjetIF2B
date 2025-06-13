#ifndef CAPTURE_H
#define CAPTURE_H

#include "game.h"

/**
 * Vérifie si une position est dans les limites du plateau.
 *
 * @param x Colonne
 * @param y Ligne
 * @param taille Taille du plateau
 * @return 1 si valide, 0 sinon
 */
int estDansLesLimites(int x, int y, int taille);

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
int capturePion(int joueur, int x, int y, int taille, TypePiece piece, Case **board);

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
int captureCavalier(int joueur, int x, int y, int taille, TypePiece piece, Case **board);

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
int captureFou(int joueur, int x, int y, int taille, TypePiece piece, Case **board);

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
int captureTour(int joueur, int x, int y, int taille, TypePiece piece, Case **board);

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
int captureDame(int joueur, int x, int y, int taille, TypePiece piece, Case **board);

/**
 * Capture avec un roi (cases adjacentes).
 *
 * @param joueur Couleur du joueur (BLANC ou NOIR)
 * @param x Coordonnée ligne
 * @param y Coordonnée colonne
 * @param taille Taille du plateau
 * @param piece Type de la pièce (ROI)
 * @param board Plateau de jeu
 * @return 1 si capture effectuée, 0 sinon
 */
int captureRoi(int joueur, int x, int y, int taille, TypePiece piece, Case **board);

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
int capturerSelonPiece(int joueur, TypePiece piece, int x, int y, int taille, Case **board);

#endif