//
// Created by Nathan on 23/01/2023.
//
#include "../headers/brique.h"
#include "../headers/main.h"
#include "../headers/score.h"
#include "../headers/tableau.h"
#include "../headers/powerups.h"

#define PT_SCORE 100

void donnerCoords(brique *brique, unsigned short posx, unsigned short posy){
    brique->x_coin_hautGauche = posx * (ScrWidth/NbBriqueLongueur);
    brique->y_coin_hautGauche = posy * (ScrHeight/(NbBriqueHauteur*2));
    brique->x_coin_basDroite = (posx+1) * (ScrWidth/NbBriqueLongueur);
    brique->y_coin_basDroite = (posy+1) * (ScrHeight/(NbBriqueHauteur*2));
}

void casseLaBrique(brique *brique, int i, int j){
    switch(brique->id){
        case 1 :
            brique->id = 0;
            if(rand()%1000<10){
                generePowerup('?');
            }
            ajoutScore(PT_SCORE);
            break;
        case 2:
            brique->id =1;
            ajoutScore(PT_SCORE);
            break;
        case 4 :
            brique->id = 0;
            generePowerup('?');
            ajoutScore(PT_SCORE*5);
            break;
        case 5 :
            brique->id = 0;
            explosionBrique(i, j);
            ajoutScore(PT_SCORE*5);
            break;
        case 6 :
            brique->id = 0;
            inverse_commande = !inverse_commande;
            ajoutScore(PT_SCORE*5);
            break;
        case 7 :
            brique->id = 0;
            generePowerup('+');
            ajoutScore(PT_SCORE*10);
            break;
        default :
            break;
    }
}
