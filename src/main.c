//
// Created by Nathan on 23/01/2023.
//
#include "../headers/main.h"
#include "../headers/barre.h"
#include "../headers/balle.h"
#include "../headers/brique.h"
#include "../headers/score.h"
#include "../headers/vies.h"
#include "../headers/tableau.h"
#include "../headers/powerup_objet.h"
#include "../headers/powerup_pouvoir.h"


#include <time.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>





unsigned short ScrWidth = 0 , ScrHeight = 0;
unsigned short niveau = 0;
bool inverse_commande = false;
bool rejouer = true;
SDL_Color blanc = {255, 255, 255}; // Blanc

int main(int argc, char *argv[]) {
    srand((unsigned long) time(0));

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    TTF_Font *police = TTF_OpenFont(FONT_PATH, 16);
    printf("%s",SDL_GetBasePath());
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    ScrWidth = DM.w-200, ScrHeight = DM.h-100;


    window = SDL_CreateWindow("Casse-briques",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              ScrWidth, ScrHeight,
                              SDL_WINDOW_ALLOW_HIGHDPI);

    renderer = SDL_CreateRenderer(window, -1, 0);

    affichageTitrePlaceHolder(renderer,police);

    SDL_Event event;

    // boucle d'initialisation de la partie : menu start
    while (1) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN || event.type == SDL_QUIT) {
                break;
            }
        }
    }
    while(rejouer) {
        InitBarre();
        score = 0;
        vies = 3;
        niveau = 0;
        reset(true);
        affichage(renderer, police);

        //boucle de jeu : tant qu'on n'a pas de game over
        while (event.type != SDL_QUIT &&
               vies > 0) { // remplacer cette condition par game over() == 0 && event.type != SDL_QUIT plus tard
            SDL_PollEvent(&event);
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if ((state[SDL_SCANCODE_A] && !inverse_commande) || (state[SDL_SCANCODE_D] && inverse_commande)) {
                if (deplacement('G')) {
                }
            }
            if ((state[SDL_SCANCODE_D] && !inverse_commande) || (state[SDL_SCANCODE_A] && inverse_commande)) {
                if (deplacement('D')) {
                }
            }
            if (state[SDL_SCANCODE_SPACE]) {
                balle1.freeze = false;
                if (barre1.magnetique == 1) {
                    barre1.magnetique = 0;
                }
            }

            updateBalle(&balle1);
            updatePowerup();
            CheckTimer();
            affichage(renderer, police);
        }
        // écran final
        affichageEcranFinal(renderer);
        if (event.type != SDL_QUIT) {
            SDL_Delay(5000);
        }
        while (event.type != SDL_QUIT) {
            if (SDL_PollEvent(&event)) {
                if (event.type == SDL_KEYDOWN || event.type == SDL_QUIT){
                    break;
                }
            }
        }
        if (event.type == SDL_QUIT){
            rejouer = false;
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
void affichageEcranFinal(SDL_Renderer *renderer) {
    TTF_Font *police = TTF_OpenFont(FONT_PATH, 50);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    char text[100] ;
    sprintf(text, "Score final : %ld",score);
    SDL_Surface *texte = TTF_RenderUTF8_Blended(police, text, blanc);
    // Création de la texture à partir de la surface
    SDL_Texture *texture1 = SDL_CreateTextureFromSurface(renderer, texte);
    // Définition de la position où afficher le texte


    SDL_Rect position1 = {(ScrWidth - texte->w) / 2, (ScrHeight - texte->h) / 2, texte->w, texte->h};
    // Affichage du texte
    SDL_RenderCopy(renderer, texture1, NULL, &position1);
    // Libération de la mémoire
    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texture1);
    TTF_CloseFont(police);

    SDL_RenderPresent(renderer);
}

void affichageTitrePlaceHolder(SDL_Renderer *renderer, TTF_Font *police) {

    TTF_Font *police2 = TTF_OpenFont(FONT_PATH, 90);
    TTF_Font *police3 = TTF_OpenFont(FONT_PATH, 40);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_Surface *texte = TTF_RenderUTF8_Blended(police2, "CASSE-BRIQUES", blanc);
    SDL_Surface *texte2 = TTF_RenderUTF8_Blended(police3, "Appuie sur un bouton pour commencer", blanc);
    SDL_Surface *texte3 = TTF_RenderUTF8_Blended(police, "par NATHAN TASTET pour CODE ALPHA - 2023", blanc);
    // Création de la texture à partir de la surface
    SDL_Texture *texture1 = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(renderer, texte2);
    SDL_Texture *texture3 = SDL_CreateTextureFromSurface(renderer, texte3);
    // Définition de la position où afficher le texte
    SDL_Rect position1 = {(ScrWidth - texte->w) / 2, 3*ScrHeight/10, texte->w, texte->h};
    SDL_Rect position2 = {(ScrWidth - texte2->w) / 2, 5*ScrHeight/10, texte2->w, texte2->h};
    SDL_Rect position3 = {(ScrWidth - texte3->w) / 2, 13*ScrHeight/20, texte3->w, texte3->h};
    // Affichage du texte
    SDL_RenderCopy(renderer, texture1, NULL, &position1);
    SDL_RenderCopy(renderer, texture2, NULL, &position2);
    SDL_RenderCopy(renderer, texture3, NULL, &position3);

    // Libération de la mémoire
    SDL_FreeSurface(texte);
    SDL_FreeSurface(texte2);
    SDL_FreeSurface(texte3);
    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    SDL_DestroyTexture(texture3);
    TTF_CloseFont(police2);
    TTF_CloseFont(police3);
    SDL_RenderPresent(renderer);
}

void affichage(SDL_Renderer *renderer, TTF_Font *police) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    //affichage des briques
    for (int i =0; i<NbBriqueLongueur ; i++) {
        for (int j = NbBriqueHauteur-1 ; j >=0 ; j--) { // on affiche à l'envers ici pour bien afficher les pwups
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
                    SDL_SetRenderDrawColor(renderer, 255, 184, 28, 0);
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

            // on génére les powerups s'il y en a
            if(briques[i][j].pw_up > 0){
                if(briques[i][j].pw_up > 4){
                    SDL_SetRenderDrawColor(renderer, 255, 184, 28, 0);
                }
                else{
                    SDL_SetRenderDrawColor(renderer, 187, 0, 0, 0);
                }
                rect.x = briques[i][j].pwup_posx- TAILLEPWUP;
                rect.y = briques[i][j].pwup_posy- TAILLEPWUP;;
                rect.w = 2 * TAILLEPWUP;
                rect.h = 2 * TAILLEPWUP;
                SDL_RenderFillRect(renderer, &rect);
            }
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

    // Création de la surface contenant le texte
    char text[100];
    sprintf(text, "Vies : %d - Score : %ld - Niveau : %d", vies, score, niveau);
    SDL_Surface *texte = TTF_RenderUTF8_Blended(police, text, blanc);
    // Création de la texture à partir de la surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, texte);
    // Définition de la position où afficher le texte
    SDL_Rect position = {0, 35*ScrHeight/36, texte->w, texte->h};
    // Affichage du texte
    SDL_RenderCopy(renderer, texture, NULL, &position);
    // Libération de la mémoire
    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texture);

    // fin affichage
    SDL_RenderPresent(renderer);
}

void reset(bool niveaufini){
    double angle = rand()%60 + 60;
    angle = angleDegreVersRadian(angle);
    initBalle(&balle1, barre1.posCentre,barre1.positionyBarre-barre1.Hauteur-0.01 * ScrHeight, VITESSE_BOULE, angle);
    balle1.freeze = true;
    barre1.magnetique = 1;
    if(niveaufini) {
        genererTableau();
        niveau++;
    }
    reinitCollision(NbBriqueLongueur+1,NbBriqueHauteur+1);
}