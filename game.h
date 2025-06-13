#ifndef GAME_H
#define GAME_H

/**
 * Couleurs possibles pour le texte et le fond dans la console.
 */
typedef enum {
    BLACK = 0,
    BLEU_FONCE,
    VERT_FONCE,
    CYAN_FONCE,
    ROUGE_FONCE,
    VIOLET,
    JAUNE_FONCE,
    GRIS_CLAIR,
    GRIS_FONCE,
    BLEU_CLAIR,
    VERT_CLAIR,
    CYAN_CLAIR,
    ROUGE_CLAIR,
    ROSE,
    JAUNE,
    WHITE
    // 0     1          2           3          4           5        6           7          8          9          10         11         12         13     14      15
} Couleur;

/**
 * Types de pièces possibles sur l'échiquier.
 */
typedef enum {
    VIDE = 0,
    PION,
    CAVALIER,
    FOU,
    TOUR,
    DAME,
    ROI
    // 0     1      2        3         4       5      6
} TypePiece;

/**
 * Couleurs des pièces (joueurs).
 */
typedef enum {
    NONE = 0,
    BLANC,
    NOIR
    // 0    1      2
} Couleurs;

/**
 * Structure représentant une case de l'échiquier.
 */
typedef struct {
    TypePiece contenu;         // Type de la pièce sur la case
    TypePiece captureeParPiece;// Type de la pièce ayant capturée la case
    Couleurs couleurPiece;    // Couleur de la pièce sur la case (BLANC/NOIR/NONE)
    Couleurs captured;        // Couleur du joueur qui a capturé la pièce
} Case;




/**
 * Retourne le symbole Unicode correspondant à une pièce d'échecs
 * en fonction de son type et de sa couleur.
 *
 * @param piece Le type de la pièce
 * @param couleur La couleur de la pièce
 * @return Une chaîne représentant le symbole Unicode
 */
const char* get_unicode_piece(TypePiece piece, Couleurs couleur);

/**
 * Fonction affichant les couleurs sur le texte et le fond
 *
 * @param texte Couleur choisie pour le texte
 * @param fond Couleur choisie pour le fond
 */
void setColor(Couleur texte, Couleur fond);

/**
 * Affiche les lettres de colonnes en haut et en bas du plateau
 *
 * @param taille La taille du plateau (nb de colonnes)
 */
void afficherColonnes(int taille);

/**
 * Affiche l’état actuel du plateau avec les pièces et les couleurs de fond.
 *
 * @param taille La taille du plateau
 * @param board Le plateau de jeu (Matrice 2D dynamique de Case)
 */
void afficherPlateau(int taille, Case **board);

/**
 * Fonction calculant et affichant les scores des deux joueurs
 *
 * @param taille Taille du plateau
 * @param board Plateau de jeu
 */
void scorer(int taille, Case **board);

/**
 * Vide le plateau
 *
 * @param taille La taille du plateau (nb de colonnes)
 * @param board Le plateau
 */
void gameEnd(int taille, Case **board);

/**
 * Gère le tour complet d’un joueur : choix d'action, pose de pièce, abandon ou sauvegarde.
 *
 * @param joueur Le joueur courant (BLANC ou NOIR)
 * @param taille La taille du plateau
 * @param modeJeu Le mode de jeu sélectionné
 * @param totalPieces Tableau contenant les pièces restantes pour chaque joueur
 * @param board Plateau de jeu (Matrice 2D dynamique)
 *@return
 */
int gameTurn(int joueur, int taille, int modeJeu, int totalPieces[3][7], Case **board);

/**
 * Lance une nouvelle partie ou charge une sauvegarde selon le choix du menu.
 *
 * @param menu 1 pour nouvelle partie, 2 pour chargement de sauvegarde
 */
void game(int menu);

#endif