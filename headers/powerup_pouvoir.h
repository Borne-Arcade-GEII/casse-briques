//
// Created by Nathan on 25/01/2023.
//

#ifndef CASSE_BRIQUES_POWERUP_POUVOIR_H
#define CASSE_BRIQUES_POWERUP_POUVOIR_H

#include <SDL_stdinc.h>
#include "brique.h"

#define DUREE_PWUP 15000
extern Uint64 timer[10] ;
void CheckTimer();

void activerPwUp(brique *brique1);
void desactiverPWUP(unsigned short i);

#endif //CASSE_BRIQUES_POWERUP_POUVOIR_H
