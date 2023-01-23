//
// Created by Nathan on 23/01/2023.
//

#include "../headers/barre.h"
#include "../headers/brique.h"
#include "../headers/powerups.h"
#include "../headers/score.h"
#include "../headers/vies.h"
#include "../headers/tableau.h"


#include <time.h>
#include <stdlib.h>

#include <SDL2/SDL.h>


int main(int argc, char *argv[]) {
    srand((unsigned long) time(0));

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    auto int Width = DM.w, Height = DM.h;

    window = SDL_CreateWindow("Casse-briques",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              Width - 100, Height - 100,
                              SDL_WINDOW_ALLOW_HIGHDPI);

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

    //boucle de jeu : tant qu'on a pas de gameover
    while (event.type != SDL_QUIT) { // remplacer cette condition par gameover() == 0 && event.type != SDL_QUIT plus tard
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}