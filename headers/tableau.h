//
// Created by Nathan on 23/01/2023.
//

#include <stdbool.h>
#include "main.h"

#ifndef CASSE_BRIQUES_TABLEAU_H
#define CASSE_BRIQUES_TABLEAU_H


extern brique briques[NbBriqueLongueur][NbBriqueHauteur] ;

void genererTableau(); // utilisé pour générer un tableau / un niveau
void afficheTab(); // pour afficher le tableau à des fins de test
bool pasDeBriqueInvincibleACote(unsigned short i,unsigned short j); // pour savoir si y'a pas de brique invincible à coté
#endif //CASSE_BRIQUES_TABLEAU_H
