//
// Created by Nathan on 23/01/2023.
//
#include "../headers/brique.h"
#include "../headers/main.h"
#include "../headers/score.h"
#include "../headers/tableau.h"

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
                generePowerup( brique, '?');
            }
            ajoutScore(PT_SCORE);
            break;
        case 2:
            brique->id =1;
            ajoutScore(PT_SCORE);
            break;
        case 4 :
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
            brique->id = 0;
            inverse_commande = !inverse_commande;
            ajoutScore(PT_SCORE*5);
            break;
        case 7 :
            brique->id = 0;
            generePowerup(brique,'+');
            ajoutScore(PT_SCORE*10);
            break;
        default :
            break;
    }
    if(tableauFini()){
        resetNiveau();
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

void activerPwUp(brique *brique1){
    printf("Powerup %hu ACTIVE WAOUH\n", brique1->pw_up);
}
