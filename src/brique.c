//
// Created by Nathan on 23/01/2023.
//
#include "../headers/brique.h"
#include "../headers/main.h"

void donnerCoords(brique *brique, unsigned short posx, unsigned short posy){
    brique->x_coin_hautGauche = posx * (ScrWidth/NbBriqueLongueur);
    brique->y_coin_hautGauche = posy * (ScrHeight/(NbBriqueHauteur*2));
    brique->x_coin_basDroite = (posx+1) * (ScrWidth/NbBriqueLongueur);
    brique->y_coin_basDroite = (posy+1) * (ScrHeight/(NbBriqueHauteur*2));
}

