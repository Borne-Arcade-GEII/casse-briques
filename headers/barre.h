//
// Created by Nathan on 23/01/2023.
//

#ifndef CASSE_BRIQUES_BARRE_H
#define CASSE_BRIQUES_BARRE_H

#include <stdbool.h>

struct barre {
    unsigned short posCentre;
    unsigned short Longueur; // faire x2 c'est la longueur que d'un coté
    unsigned short Hauteur;
    unsigned short positionyBarre;
    bool magnetique;
    bool controle_inverse;
};
typedef struct barre barre;
extern barre barre1;

void InitBarre();
void transfereTailleEcran(int Width, int Height);
bool deplacement(char direction);
#endif //CASSE_BRIQUES_BARRE_H
