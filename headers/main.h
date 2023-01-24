//
// Created by Nathan on 24/01/2023.
//

#ifndef CASSE_BRIQUES_MAIN_H
#define CASSE_BRIQUES_MAIN_H

#define NbBriqueLongueur 12 //  nombre de briques en longueur
#define NbBriqueHauteur 9 // nombre de briques en hauteur
#include <SDL2/SDL.h>
#include "barre.h"
#include "brique.h"
#include "balle.h"

extern unsigned short ScrWidth, ScrHeight;
extern bool inverse_commande;
void affichage(SDL_Renderer *renderer);
void resetNiveau();
#endif //CASSE_BRIQUES_MAIN_H
