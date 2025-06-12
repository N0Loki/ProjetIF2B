#ifndef MOVES_H
#define MOVES_H

#include "game.h"

/**
 * Vérifie s'il reste des pièces à poser pour un joueur donné
 *
 * @param joueur Couleur du joueur (BLANC ou NOIR)
 * @return 1 s'il reste des pièces, 0 sinon
 */
int reste_piece(Couleurs joueur, int totalPieces[3][7]);


/**
 * Affiche les pièces restantes du joueur.
 *
 * @param joueur Le joueur actif (BLANC ou NOIR).
 * @param totalPieces Tableau des pièces restantes [3][7] pour chaque joueur :
 *                    totalPieces[joueur][typePiece] donne le nombre restant.
 */
void afficher_Pieces_restantes(int joueur, int totalPieces[3][7]);

/**
 * Fonction convertissant une chaîne de caractères en minuscules
 *
 * @param str Chaîne à convertir
 */
void toLowercase(char *str);

/**
 * Fonction convertissant une lettre représentant une colonne en indice
 *
 * @param lettre Lettre représentant une colonne
 * @return Indice correspondant
 */
int transLettre(char lettre);

/**
 * Retourne le nom textuel d'une pièce d'échecs selon son type.
 *
 * Cette fonction permet d'afficher des messages plus lisibles pour les joueurs,
 * en convertissant une valeur de l'énumération TypePiece en une chaîne de caractères.
 *
 * @param piece Le type de pièce (PION, CAVALIER, FOU, TOUR, DAME, ROI)
 * @return const char* Le nom de la pièce en français. "Inconnue" si le type est invalide.
 */
const char* nomPiece(TypePiece piece);

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
int poser_et_valider_piece(int joueur, TypePiece piece, int x, int y, int taille, int modeJeu, Case **board);

/**
 * Demande au joueur de choisir une pièce parmi celles qu'il possède encore.
 *
 * @param joueur Couleur du joueur (BLANC ou NOIR)
 * @param totalPieces Tableau des pièces restantes pour chaque joueur [3][7]
 * @return TypePiece choisie
 */
TypePiece demanderPiece(int joueur, int totalPieces[3][7]);

/**
 * Demande au joueur une position valide sur le plateau
 *
 * @param tailleEchiquier Taille du plateau
 * @param[out] x Coordonnée ligne (indexée à 0)
 * @param[out] y Coordonnée colonne (indexée à 0)
 */
void demanderPosition(int tailleEchiquier, int *x, int *y);


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
int tour_joueur_poser_piece(int joueur, int taille, int modeJeu, int totalPieces[3][7], Case **board);

#endif