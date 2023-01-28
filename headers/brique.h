//
// Created by Nathan on 23/01/2023.
//

#ifndef CASSE_BRIQUES_BRIQUE_H
#define CASSE_BRIQUES_BRIQUE_H

#include <stdbool.h>

#define TAILLEPWUP 10
#define VITESSE_CHUTE_PWP 0.05

struct brique {
    unsigned char id ;
    unsigned short x_coin_hautGauche;
    unsigned short y_coin_hautGauche;
    unsigned short x_coin_basDroite;
    unsigned short y_coin_basDroite;
    unsigned char pw_up ; // les ID de powerup vont de 1 à 9 : 1.2.3.4 = malus 5.6.7.8.9 = bonus
    float pwup_posx;
    float pwup_posy;
    bool collision;//renvoie 1 si on vient de la toucher
    unsigned short x_centre;
    unsigned short y_centre;
};

typedef struct brique brique;
void donnerCoords(brique *brique, unsigned short posx, unsigned short posy);// remplit les coordonnées xy de la brique
void casseLaBrique(brique *brique, int i, int j,bool exp);
//en fonction de la position de la brique dans le tableau
#endif //CASSE_BRIQUES_BRIQUE_H
