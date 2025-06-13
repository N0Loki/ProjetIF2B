#ifndef SAVES_H
#define SAVES_H

#include "game.h"

/**
 * Sauvegarde la partie dans un fichier texte.
 *
 * @param joueur Le joueur courant.
 * @param taille La taille du plateau.
 * @param modeJeu Le mode de jeu en cours.
 * @param totalPieces Tableau contenant les pièces restantes pour chaque joueur [3][7].
 * @param board Le plateau de jeu représenté par une matrice de structures Case.
 * @param fileName Le nom du fichier dans lequel enregistrer la sauvegarde.
 */
void createSave(int joueur, int taille, int modeJeu, int totalPieces[3][7], Case **board, char fileName[]);

/**
 * Charge une partie depuis un fichier de sauvegarde.
 *
 * @param[out] joueur Pointeur vers la variable du joueur courant.
 * @param[out] taille Pointeur vers la taille du plateau .
 * @param[out] modeJeu Pointeur vers le mode de jeu restauré.
 * @param[out] totalPieces Tableau où seront stockées les pièces restantes [3][7].
 * @param filename Nom du fichier de sauvegarde à charger.
 * @return Le plateau chargé (Case**), ou NULL en cas d’échec.
 */
Case** loadSave(int* joueur, int* taille, int* modeJeu, int totalPieces[2][7], const char* filename);

#endif