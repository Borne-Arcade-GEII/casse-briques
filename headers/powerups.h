//
// Created by Nathan on 23/01/2023.
//

#ifndef CASSE_BRIQUES_POWERUPS_H
#define CASSE_BRIQUES_POWERUPS_H
struct powerup{
    char id ;
    unsigned short x_coin_hautGauche;
};
typedef struct powerup powerup;
powerup generePowerup(char type);//génere un powerup parmi 2 types : '?' = malus et bonus; '+' = bonus seulement
#endif //CASSE_BRIQUES_POWERUPS_H
