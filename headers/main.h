//
// Created by Nathan on 24/01/2023.
//

#ifndef CASSE_BRIQUES_MAIN_H
#define CASSE_BRIQUES_MAIN_H

#define NbBriqueLongueur 12 //  nombre de briques en longueur
#define NbBriqueHauteur 9 // nombre de briques en hauteur
#define VITESSE_BOULE 0.2
#define FONT_PATH "../fonts/Font.ttf"

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include "barre.h"
#include "brique.h"
#include "balle.h"

extern unsigned short niveau ;
extern unsigned short ScrWidth, ScrHeight;
extern bool inverse_commande;

void affichageTitrePlaceHolder(SDL_Renderer *renderer, TTF_Font *police);
void affichage(SDL_Renderer *renderer, TTF_Font *police);
void affichageEcranFinal(SDL_Renderer *renderer);

void reset(bool niveaufini);//1 si le nieveau est fini 0 sinon
#endif //CASSE_BRIQUES_MAIN_H
