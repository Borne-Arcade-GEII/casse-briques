//
// Created by Nathan on 24/01/2023.
//

#ifndef CASSE_BRIQUES_MAIN_H
#define CASSE_BRIQUES_MAIN_H

#define NbBriqueLongueur 11 //  nombre de briques en longueur
#define NbBriqueHauteur 9 // nombre de briques en hauteur
#define VITESSE_BOULE 0.2
#define FONT_PATH "../fonts/Font.ttf"

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "barre.h"
#include "brique.h"
#include "balle.h"

extern unsigned short niveau ;
extern unsigned short TrueScrWidth, ScrWidth, ScrHeight;
extern bool inverse_commande;
extern Mix_Chunk *brique_cassee1;
extern Mix_Chunk *brique_cassee2;
extern Mix_Chunk *brique_cassee3;
extern Mix_Chunk *brique_cassee4;
extern Mix_Chunk *brique_cassee6;
extern Mix_Chunk *brique_cassee7;
extern Mix_Chunk *brique_explose;
extern Mix_Chunk *powerup_bonus;
extern Mix_Chunk *powerup_malus;
extern Mix_Chunk *collision_barre;

extern Mix_Chunk *collision_bord;
extern Mix_Chunk *perte_vie ;
extern Mix_Chunk *fin_niveau;
extern Mix_Chunk *musique_titre;

void affichageTitrePlaceHolder(SDL_Renderer *renderer, TTF_Font *police);
void affichage(SDL_Renderer *renderer, TTF_Font *police);
void affichageEcranFinal(SDL_Renderer *renderer);

void reset(bool niveaufini);//1 si le nieveau est fini 0 sinon
#endif //CASSE_BRIQUES_MAIN_H
