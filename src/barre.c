//
// Created by Nathan on 23/01/2023.
//

#include "../headers/barre.h"
#include "../headers/main.h"
#define VITESSE_BARRE 0.7
barre barre1 = {0, 0,0,0,1};

void InitBarre(){
    barre1.posCentre =  ScrWidth/2;
    barre1.Longueur=  ScrWidth/14;
    barre1.Hauteur =  (0.01 * ScrHeight);
    barre1.positionyBarre =  0.94 *ScrHeight ;
}

bool deplacement(char direction) {
    bool retour = false;
    if (direction == 'G' && barre1.posCentre>barre1.Longueur) { // déplacement gauche
        barre1.posCentre -= VITESSE_BARRE;
        if(balle1.freeze){
            balle1.posx -=VITESSE_BARRE;
        }
        retour = true ;
    }
    if ((direction == 'D') && (barre1.posCentre<ScrWidth- barre1.Longueur) ) { // déplacement droite
        barre1.posCentre += VITESSE_BARRE;
        if(balle1.freeze){
            balle1.posx +=VITESSE_BARRE;
        }
        retour = true ;
    }
    return retour;
}
