//
// Created by Nathan on 24/01/2023.
//

#ifndef CASSE_BRIQUES_BALLE_H
#define CASSE_BRIQUES_BALLE_H

#include <stdbool.h>

struct balle {
    float posx;
    float posy;
    float vitesse;//vitesse en coord polaire
    double angle;
    double vitessex;//vitesse en coord rect
    double vitessey;
    signed short rayon;
    bool freeze;
    bool explosive;
};
typedef struct balle balle;
extern balle balle1;

void initBalle(balle *b, int x, int y, float vitesse, float angle) ;
void updateBalle(balle *b) ;
void calculVitesseRect(balle *b);
float angleDegreVersRadian(float angleDegre);

void gereCollisionBord(balle *b);
void gereCollisionBarre(balle *b);
void gereCollisionBrique(balle *b);
#endif //CASSE_BRIQUES_BALLE_H
