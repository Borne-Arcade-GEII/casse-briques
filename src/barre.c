//
// Created by Nathan on 23/01/2023.
//

#include "../headers/barre.h"
#include "../headers/main.h"

barre barre1 = {0, 0,0,0,false,false};

void InitBarre(){
    barre1.posCentre =  ScrWidth/2;
    barre1.Longueur=  ScrWidth/14;
    barre1.Hauteur =  (0.01 * ScrHeight);
    barre1.positionyBarre =  0.9 *ScrHeight ;
}

bool deplacement(char direction) {
    bool retour = false;
    if (direction == 'G' && barre1.posCentre>barre1.Longueur) { // déplacement gauche
        barre1.posCentre--;
        retour = true ;
    }
    if ((direction == 'D') && (barre1.posCentre<ScrWidth- barre1.Longueur) ) { // déplacement droite
        barre1.posCentre++;
        retour = true ;
    }
    return retour;
}
