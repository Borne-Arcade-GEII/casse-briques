//
// Created by Nathan on 25/01/2023.
//

#ifndef CASSE_BRIQUES_POWERUP_OBJET_H
#define CASSE_BRIQUES_POWERUP_OBJET_H
#include "brique.h"
void generePowerup(brique *brique , char type);//génere un powerup parmi 2 types : '?' = malus et bonus; '+' = bonus seulement
void updatePowerup();
void gereCollisionPwBord(brique *brique1);
void gereCollisionPwBarre(brique *brique1);
#endif //CASSE_BRIQUES_POWERUP_OBJET_H
