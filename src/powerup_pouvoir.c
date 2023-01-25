//
// Created by Nathan on 25/01/2023.
//

#include <stdbool.h>
#include "../headers/powerup_pouvoir.h"
#include "../headers/main.h"
#include "../headers/vies.h"
#include "../headers/score.h"

Uint64 timer[10] = {0};

void CheckTimer(){
    Uint64 tempsActuel = SDL_GetTicks64();
    for(int i = 0; i<10; i++){
        if(timer[i]!=0){
            if(tempsActuel - timer[i] >=DUREE_PWUP){
                desactiverPWUP(i);
            }
        }
    }
}

void activerPwUp(brique *brique1){
    switch(brique1->pw_up){
        case 1 ://rétrecir taille barre
            barre1.Longueur = ScrWidth/25;
            break;
        case 2 : // inversion des controles
            inverse_commande = true;
            break;
        case 3 : // perte de pts
            ajoutScore(-PT_SCORE*100);
            break;
        case 4 :// balle rapide
            balle1.vitesse = VITESSE_BOULE * 1.5;
            calculVitesseRect(&balle1);
            break;
        case 5 ://agrandir barre
            barre1.Longueur = ScrWidth/10;
            break;
        case 6 :
            barre1.magnetique = 2;
            break;
        case 7 :
            balle1.explosive = true;
            //faire balle explosive + tard
            break;
        case 8 :
            multipts = true;
            break;
        case 9 :
            vies++;
            break;
        default:
            break;
    }
    if(brique1->pw_up != 9 && brique1->pw_up != 3){
        timer[brique1->pw_up] = SDL_GetTicks64();
    }
    ajoutScore(PT_SCORE*10);
}

void desactiverPWUP(unsigned short i){
    switch(i){
        case 1 :
        case 5 :
            barre1.Longueur = ScrWidth/14;
            break;
        case 2 :
            inverse_commande = false;
            break;
        case 4 :
            balle1.vitesse = VITESSE_BOULE;
            calculVitesseRect(&balle1);
            break;
        case 6 :
            barre1.magnetique = 0;
            break;
        case 7 :
            balle1.explosive = false;
            break;
        case 8 :
            multipts = false;
            break;
        default:
            break;
    }
    timer[i] = 0;
}