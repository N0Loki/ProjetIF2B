#include "saves.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

#define SAVE_FOLDER "Saves"
#define SAVE_FILE "savegame.txt"

#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(dir) _mkdir(dir)
#else
    #include <sys/stat.h>
    #define MKDIR(dir) mkdir((dir), 0755)
#endif


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
void createSave(int joueur, int taille, int modeJeu, int totalPieces[3][7], Case **board, char fileName[]) {

    if (MKDIR(SAVE_FOLDER) != 0 && errno != EEXIST) {
        perror("Erreur création dossier");
        exit(EXIT_FAILURE);
    }

    char path[256];
    snprintf(path, sizeof(path), "%s/%s", SAVE_FOLDER, fileName);  // Chemin complet du fichier

    FILE *f = fopen(path, "w");
    if (!f) {
        fprintf(stderr, "Erreur : impossible d’ouvrir le fichier de sauvegarde.\n");
        return;
    }

    fprintf(f, "Joueur:%d\n", joueur);
    fprintf(f, "ModeJeu:%d\n", modeJeu);
    fprintf(f, "Taille:%d\n", taille);

    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            Case c = board[i][j];
            fprintf(f, "%d %d %d ", c.contenu, c.couleurPiece, c.captured);
        }
        fprintf(f, "\n");
    }

    for (int joueur_id = 0; joueur_id <= 2; joueur_id++) {
        fprintf(f, "pieces_joueur_%d:", joueur_id);
        for (int piece = 1; piece <= 6; piece++) {
            fprintf(f, "%d ", totalPieces[joueur_id][piece]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf(" Sauvegarde effectuée dans : %s\n", path);
}


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
Case** loadSave(int* joueur, int* taille, int* modeJeu, int totalPieces[3][7], const char* filename) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", SAVE_FOLDER, filename);

    FILE *file = fopen(path, "r");
    if (!file) {
        perror("\nErreur ouverture fichier de sauvegarde\n");
        return NULL;
    }

    char buffer[256];

    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "Joueur:%d", joueur);

    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "ModeJeu:%d", modeJeu);

    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "Taille:%d", taille);

    Case** board = malloc((*taille) * sizeof(Case*));
    for (int i = 0; i < *taille; i++) {
        board[i] = malloc((*taille) * sizeof(Case));
        for (int j = 0; j < *taille; j++) {
            int contenu, couleur, captured;
            fscanf(file, "%d %d %d", &contenu, &couleur, &captured);
            board[i][j].contenu = contenu;
            board[i][j].couleurPiece = couleur;
            board[i][j].captured = captured;
        }
        fscanf(file, "\n");
    }

    for (int i = 0; i <= 2; i++) {
        fgets(buffer, sizeof(buffer), file);
        sscanf(buffer, "pieces_joueur_%*d: %d %d %d %d %d %d",
            &totalPieces[i][1], &totalPieces[i][2], &totalPieces[i][3],
            &totalPieces[i][4], &totalPieces[i][5], &totalPieces[i][6]);
    }

    fclose(file);
    printf("Sauvegarde chargée depuis : %s\n", path);
    printf("\nDébut du jeu !\n");
    return board;
}