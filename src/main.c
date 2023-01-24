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

unsigned short ScrWidth = 0 , ScrHeight = 0;

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
    balle1.posx = ScrWidth/2;
    balle1.posy = ScrHeight/2;
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    genererTableau();
    afficheTab();

    SDL_Event event;
    // boucle d'initialisation de la partie : menu start
    while (1) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN || event.type == SDL_QUIT) {
                break;
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    //boucle de jeu : tant qu'on n'a pas de game over
    while (event.type != SDL_QUIT) { // remplacer cette condition par game over() == 0 && event.type != SDL_QUIT plus tard
        SDL_Delay(0.1);
        SDL_PollEvent(&event);
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_A]) {
            if(deplacement('G')){
                affichage(renderer);
            }
        } else if (state[SDL_SCANCODE_D]) {
            if(deplacement('D')){
                affichage(renderer);
            }
        }

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
    // on génère la barre mtn, on prend que la taille standard pour l'instant faudra faire un switch pour plus tard
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rect;
    rect.x = barre1.posCentre - barre1.Longueur;
    rect.y = barre1.positionyBarre - barre1.Hauteur;
    rect.w = 2 * barre1.Longueur ;
    rect.h = 2 * barre1.Hauteur ;
    SDL_RenderFillRect(renderer, &rect);
    // on génère la balle mtn
    SDL_RenderPresent(renderer);
}