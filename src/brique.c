//
// Created by Nathan on 23/01/2023.
//

#include "../headers/brique.h"
#include "../headers/main.h"
#include "../headers/score.h"
#include "../headers/tableau.h"
#include "../headers/powerup_objet.h"
#include "../headers/powerup_pouvoir.h"

void donnerCoords(brique *brique, unsigned short posx, unsigned short posy){
    brique->x_coin_hautGauche = posx * (ScrWidth/NbBriqueLongueur);
    brique->y_coin_hautGauche = posy * (ScrHeight/(NbBriqueHauteur*2));
    brique->x_coin_basDroite = (posx+1) * (ScrWidth/NbBriqueLongueur);
    brique->y_coin_basDroite = (posy+1) * (ScrHeight/(NbBriqueHauteur*2));
    brique->x_centre = brique->x_coin_hautGauche + (brique->x_coin_basDroite-brique->x_coin_hautGauche)/2;
    brique->y_centre = brique->y_coin_hautGauche + (brique->y_coin_basDroite-brique->y_coin_hautGauche)/2;

}

void casseLaBrique(brique *brique, int i, int j,bool exp){
    switch(brique->id){
        case 1 :
            if(!exp) {
                Mix_PlayChannel(-1, brique_cassee1, 0);
            }
            brique->id = 0;
            ajoutScore(PT_SCORE);
            break;
        case 2:
            if(exp){
                brique->id = 0;
                ajoutScore(PT_SCORE);
            }else{
                Mix_PlayChannel(-1, brique_cassee2, 0);
                brique->id = 1;
            }
            ajoutScore(PT_SCORE);
            break;
        case 3 :
            if(!exp) {
                Mix_PlayChannel(-1, brique_cassee3, 0);
            }
            break;
        case 4 :
            if(!exp) {
                Mix_PlayChannel(-1, brique_cassee4, 0);
            }
            brique->id = 0;
            generePowerup(brique,'?');
            ajoutScore(PT_SCORE*5);
            break;
        case 5 :
            brique->id = 0;
            explosionBrique(i, j);
            ajoutScore(PT_SCORE*5);
            break;
        case 6 :
            if(!exp) {
                Mix_PlayChannel(-1, brique_cassee6, 0);
            }
            brique->id = 0;
            inverse_commande = true;
            timer[2] = SDL_GetTicks();
            ajoutScore(PT_SCORE*5);
            break;
        case 7 :
            if(!exp) {
                Mix_PlayChannel(-1, brique_cassee7, 0);
            }
            brique->id = 0;
            generePowerup(brique,'+');
            ajoutScore(PT_SCORE*10);
            break;
        default :
            break;
    }
    if(tableauFini()){
        reset(true);
    }
}


