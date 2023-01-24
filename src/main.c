//
// Created by Nathan on 23/01/2023.
//
#include "../headers/main.h"
#include "../headers/barre.h"
#include "../headers/balle.h"
#include "../headers/brique.h"
#include "../headers/powerups.h"
#include "../headers/score.h"
#include "../headers/vies.h"
#include "../headers/tableau.h"


#include <time.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#define VITESSE_BOULE 0.2

unsigned short ScrWidth = 0 , ScrHeight = 0;
bool inverse_commande = false;

int main(int argc, char *argv[]) {
    srand((unsigned long) time(0));

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    ScrWidth = DM.w-100, ScrHeight = DM.h-100;


    window = SDL_CreateWindow("Casse-briques",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              ScrWidth, ScrHeight,
                              SDL_WINDOW_ALLOW_HIGHDPI);
    InitBarre();
    double angle = rand()%60 + 60;
    angle = angleDegreVersRadian(angle);
    initBalle(&balle1, barre1.posCentre,barre1.positionyBarre-barre1.Hauteur-0.01 * ScrHeight, VITESSE_BOULE, angle);

    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);



    SDL_Event event;
    // boucle d'initialisation de la partie : menu start
    while (1) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN || event.type == SDL_QUIT) {
                break;
            }
        }
    }

    genererTableau();
    affichage(renderer);

    //boucle de jeu : tant qu'on n'a pas de game over
    while (event.type != SDL_QUIT) { // remplacer cette condition par game over() == 0 && event.type != SDL_QUIT plus tard
        SDL_PollEvent(&event);
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if ((state[SDL_SCANCODE_A] && !inverse_commande) || (state[SDL_SCANCODE_D] && inverse_commande)  ) {
            if(deplacement('G')){
            }
        } else if ((state[SDL_SCANCODE_D] && !inverse_commande) || (state[SDL_SCANCODE_A] && inverse_commande)) {
            if(deplacement('D')){
            }
        }
        else if(state[SDL_SCANCODE_SPACE]){
            balle1.freeze = false;
            if(barre1.magnetique == 1){
                barre1.magnetique = 0;
            }
        }

        updateBalle(&balle1);
        affichage(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}

void affichage(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    //affichage des briques
    for (int i =0; i<NbBriqueLongueur ; i++) {
        for (int j = 0; j < NbBriqueHauteur; j++) {
            switch (briques[i][j].id) {
                case 0 :
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                    break;
                case 1 :
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
                    break;
                case 2:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
                    break;
                case 3:
                    SDL_SetRenderDrawColor(renderer, 155, 155, 155, 0);
                    break;
                case 4 :
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
                    break;
                case 5 :
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
                    break;
                case 6 :
                    SDL_SetRenderDrawColor(renderer, 238, 130, 238, 0);
                    break;
                case 7 :
                    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
                    break;
                default :
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                    break;
            }
            SDL_Rect rect;
            rect.x = briques[i][j].x_coin_hautGauche;
            rect.y = briques[i][j].y_coin_hautGauche;
            rect.w = briques[i][j].x_coin_basDroite - rect.x;
            rect.h = briques[i][j].y_coin_basDroite - rect.y;
            SDL_RenderFillRect(renderer, &rect);

        }
    }
    // on génère la barre mtn, on prend que la taille standard pour l'instant il faudra faire un switch pour plus tard
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rect;
    rect.x = barre1.posCentre - barre1.Longueur;
    rect.y = barre1.positionyBarre - barre1.Hauteur;
    rect.w = 2 * barre1.Longueur ;
    rect.h = 2 * barre1.Hauteur ;
    SDL_RenderFillRect(renderer, &rect);
    // on génère la balle mtn
    for (int w = 0; w < balle1.rayon * 2; w++) {
        for (int h = 0; h < balle1.rayon * 2; h++) {
            int dx = balle1.rayon - w; // horizontal offset
            int dy = balle1.rayon - h; // vertical offset
            if ((dx * dx + dy * dy) <= (balle1.rayon * balle1.rayon)) {
                SDL_RenderDrawPoint(renderer, balle1.posx + dx, balle1.posy + dy);
            }
        }
    }
    SDL_RenderPresent(renderer);
}