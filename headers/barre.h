//
// Created by Nathan on 23/01/2023.
//

#ifndef CASSE_BRIQUES_BARRE_H
#define CASSE_BRIQUES_BARRE_H

#include <stdbool.h>

struct barre {
    float posCentre;
    unsigned short Longueur; // faire x2 c'est la longueur que d'un coté
    unsigned short Hauteur;
    unsigned short positionyBarre;
    unsigned short magnetique; // 1 si magnétique temp : début de partie; 2 si magnétique grâce au power up qui persiste
    bool controle_inverse;
};
typedef struct barre barre;
extern barre barre1;

void InitBarre();
bool deplacement(char direction);
#endif //CASSE_BRIQUES_BARRE_H
