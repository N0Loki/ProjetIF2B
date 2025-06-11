
#ifndef SETUP_H
#define SETUP_H

typedef enum {
    Vide,Pion, Fou, Cavalier, Tour, Dame, Roi
    //0 ,  1 ,  2 ,    3    ,  4  ,  5  ,  6
}TypePiece;

typedef enum {
    None, Blanc, Noir
    //0  ,  1  ,  2
}Couleurs;

typedef struct {
    TypePiece contenu;
    Couleurs couleurPiece;
    Couleurs captured;
}Case;

#endif //SETUP_H
