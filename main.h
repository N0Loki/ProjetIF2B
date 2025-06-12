#ifndef MAIN_H
#define MAIN_H

/**
 * Lance la fonction principale de jeu selon le choix (nouvelle partie ou chargement).
 * @param choix Entier représentant le choix de l'utilisateur (1 ou 2)
 */
void game(int choix);

/**
 * Fonction responsable du chargement ou de la gestion des sauvegardes.
 */
void saves();

/**
 * Initialise les paramètres nécessaires à l'affichage Unicode dans le terminal.
 */
void include_uni();

#endif