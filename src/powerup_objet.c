//
// Created by Nathan on 24/01/2023.
//

#include <stdlib.h>
#include "../headers/brique.h"
#include "../headers/main.h"
#include "../headers/tableau.h"
#include "../headers/score.h"
#include "../headers/powerup_pouvoir.h"

void gereCollisionPwBord(brique *brique1){
    if(brique1->pwup_posy > ScrHeight){
        brique1->pw_up = 0;
    }
}
void gereCollisionPwBarre(brique *brique1){
    if(brique1->pwup_posx > barre1.posCentre-barre1.Longueur && brique1->pwup_posx < barre1.posCentre+barre1.Longueur) {
        if (brique1->pwup_posy > barre1.positionyBarre - barre1.Hauteur &&
            brique1->pwup_posy  < barre1.positionyBarre + barre1.Hauteur) {
            activerPwUp(brique1);
            brique1->pw_up = 0;
        }
    }
}

void generePowerup(brique *brique , char type){
    brique->pw_up = rand()% 9 + 1;
    if(type == '+' && brique->pw_up <= 4){
        brique->pw_up+= 5;
    }
    brique->pwup_posx = (brique->x_coin_basDroite + brique->x_coin_hautGauche)/2;
    brique->pwup_posy = (brique->y_coin_basDroite + brique->y_coin_hautGauche)/2;
    brique->pwup_vitesse_chute = VITESSE_CHUTE_PWP;
}

void updatePowerup(){
    for(unsigned short i = 0; i < NbBriqueLongueur; i++){
        for(unsigned short  j = 0; j < NbBriqueHauteur; j++) {
            if(briques[i][j].pw_up > 0){
                briques[i][j].pwup_posy += VITESSE_CHUTE_PWP;
                gereCollisionPwBord(&briques[i][j]);
                gereCollisionPwBarre(&briques[i][j]);
            }
        }
    }
}



