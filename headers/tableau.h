//
// Created by Nathan on 23/01/2023.
//

#include <stdbool.h>
#include "main.h"

#ifndef CASSE_BRIQUES_TABLEAU_H
#define CASSE_BRIQUES_TABLEAU_H


extern brique briques[NbBriqueLongueur][NbBriqueHauteur] ;

struct limites{
    signed short limA;
    signed short limB;
    signed short limC;
    signed short limD;
};
typedef struct limites limites;

void genererTableau(); // utilisé pour générer un tableau / un niveau
bool pasDeBriqueInvincibleACote(unsigned short i,unsigned short j); // pour savoir s'il n'y a pas de brique invincible à coté
void explosionBrique(unsigned short i,unsigned short j); // faire péter les briques à coté ! ! !

#endif //CASSE_BRIQUES_TABLEAU_H
