//
// Created by Nathan on 23/01/2023.
//

#ifndef CASSE_BRIQUES_BRIQUE_H
#define CASSE_BRIQUES_BRIQUE_H
struct brique {
    char id ;
    unsigned short x_coin_hautGauche;
    unsigned short y_coin_hautGauche;
    unsigned short x_coin_basDroite;
    unsigned short y_coin_basDroite;
};
typedef struct brique brique;
void donnerCoords(brique *brique, unsigned short posx, unsigned short posy);// remplit les coordonnées xy de la brique
//en fonction de la position de la brique dans le tableau
#endif //CASSE_BRIQUES_BRIQUE_H
