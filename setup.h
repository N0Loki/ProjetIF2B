#ifndef SETUP_H
#define SETUP_H

#include "game.h"

/**
 * Active le support UTF-8 dans la console Windows.
 * Ne fait rien sur les autres systèmes.
 */
void include_uni(void);

/**
 * Choisit aléatoirement quel joueur commence.
 *
 * @return 1 pour le joueur blanc, 2 pour le joueur noir.
 */
int choix_joueur(void);

/**
 * Demande à l'utilisateur de choisir une taille de plateau entre 6 et 12.
 *
 * @return La taille choisie par l'utilisateur.
 */
int choix_taille(void);

/**
 * Demande à l'utilisateur de choisir le mode de jeu.
 *
 * @return 1 pour le mode Conquête, 2 pour le mode Connecte.
 */
int choix_mode(void);

/**
 * Alloue dynamiquement un plateau carré de la taille spécifiée et initialise chaque case.
 *
 * @param size La taille du plateau (nombre de lignes et de colonnes).
 * @return Un tableau 2D de pointeurs vers des structures Case initialisées.
 */
Case** create_board(int size);

/**
 * Initialise tous les paramètres de la partie (console UTF-8, joueur aléatoire,
 * taille du plateau, mode de jeu, et création du plateau).
 *
 * @param joueur Pointeur vers la variable qui contiendra le joueur qui commence (1 ou 2).
 * @param taille Pointeur vers la variable qui contiendra la taille du plateau.
 * @param modeJeu Pointeur vers la variable qui contiendra le mode de jeu choisi.
 * @param board Pointeur vers le plateau 2D de jeu à initialiser.
 */
void setup(int* joueur, int* taille, int* modeJeu, Case*** board);

#endif
