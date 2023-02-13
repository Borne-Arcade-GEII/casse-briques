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


Mix_Chunk *brique_cassee1 = NULL;
Mix_Chunk *brique_cassee2 = NULL;
Mix_Chunk *brique_cassee3 = NULL;
Mix_Chunk *brique_cassee4 = NULL;
Mix_Chunk *brique_cassee6 = NULL;
Mix_Chunk *brique_cassee7 = NULL;
Mix_Chunk *brique_explose = NULL;
Mix_Chunk *powerup_bonus = NULL;
Mix_Chunk *powerup_malus = NULL;
Mix_Chunk *collision_barre = NULL;
Mix_Chunk *collision_bord = NULL;
Mix_Chunk *perte_vie = NULL;
Mix_Chunk *fin_niveau = NULL;


SDL_Texture *agrandissement = NULL;
SDL_Texture *aimant = NULL;
SDL_Texture *brique_1coup = NULL;
SDL_Texture *brique_2coup = NULL;
SDL_Texture *brique_metal = NULL;
SDL_Texture *brique_bonus = NULL;
SDL_Texture *brique_powerup = NULL;
SDL_Texture *brique_reverse = NULL;
SDL_Texture *brique_TNT = NULL;
SDL_Texture *multi_piece = NULL;
SDL_Texture *perte_piece = NULL;
SDL_Texture *piece_classique = NULL;
SDL_Texture *retrecissement = NULL;
SDL_Texture *reverse = NULL;
SDL_Texture *ajout_vie = NULL;
SDL_Texture *explosif = NULL;
SDL_Texture *balle_rapide = NULL;



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
    IMG_Init(IMG_INIT_PNG);


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

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    brique_cassee1 = Mix_LoadWAV("../sounds/brique_cassee1.wav");
    brique_cassee2 = Mix_LoadWAV("../sounds/brique_cassee2.wav");
    brique_cassee3 = Mix_LoadWAV("../sounds/brique_cassee3.wav");
    brique_cassee4 = Mix_LoadWAV("../sounds/brique_cassee4.wav");
    brique_cassee6 = Mix_LoadWAV("../sounds/brique_cassee6.wav");
    brique_cassee7 = Mix_LoadWAV("../sounds/brique_cassee7.wav");
    brique_explose = Mix_LoadWAV("../sounds/explosion.wav");
    powerup_bonus = Mix_LoadWAV("../sounds/powerup_bonus.wav");
    powerup_malus = Mix_LoadWAV("../sounds/powerup_malus.wav");
    collision_barre = Mix_LoadWAV("../sounds/collision_barre.wav");
    collision_bord = Mix_LoadWAV("../sounds/collision_bord.wav");
    perte_vie = Mix_LoadWAV("../sounds/perte_vie.wav");
    fin_niveau = Mix_LoadWAV("../sounds/fin_niveau.wav");

    agrandissement = IMG_LoadTexture(renderer, "../assets/agrandissement.png");
    aimant = IMG_LoadTexture(renderer, "../assets/aimant.png");
    brique_1coup = IMG_LoadTexture(renderer, "../assets/brique_1coup.png");
    brique_2coup = IMG_LoadTexture(renderer, "../assets/brique_2coup.png");
    brique_bonus = IMG_LoadTexture(renderer, "../assets/brique_bonus.png");
    brique_powerup = IMG_LoadTexture(renderer, "../assets/brique_powerup.png");
    brique_reverse = IMG_LoadTexture(renderer, "../assets/brique_reverse.png");
    brique_metal = IMG_LoadTexture(renderer, "../assets/brique_metal.png");
    brique_TNT = IMG_LoadTexture(renderer, "../assets/brique_TNT.png");
    multi_piece = IMG_LoadTexture(renderer, "../assets/multi_piece.png");
    perte_piece = IMG_LoadTexture(renderer, "../assets/perte_piece.png");
    piece_classique = IMG_LoadTexture(renderer, "../assets/piece_classique.png");
    retrecissement = IMG_LoadTexture(renderer, "../assets/retrecissement.png");
    reverse = IMG_LoadTexture(renderer, "../assets/reverse.png");
    explosif = IMG_LoadTexture(renderer, "../assets/explosif.png");
    ajout_vie = IMG_LoadTexture(renderer, "../assets/ajout_vie.png");
    balle_rapide = IMG_LoadTexture(renderer, "../assets/balle_rapide.png");

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
        vies = 2;
        niveau = 0;
        reset(true);
        affichage(renderer, police);

        //boucle de jeu : tant qu'on n'a pas de game over
        while (event.type != SDL_QUIT && vies > 0) {
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
    SDL_Rect rect;
    //affichage des briques
    for (int i =0; i<NbBriqueLongueur ; i++) {
        for (int j = NbBriqueHauteur-1 ; j >=0 ; j--) { // on affiche à l'envers ici pour bien afficher les pwups
            if(briques[i][j].id != 0) {
                rect.x = briques[i][j].x_coin_hautGauche;
                rect.y = briques[i][j].y_coin_hautGauche;
                rect.w = briques[i][j].x_coin_basDroite - rect.x;
                rect.h = briques[i][j].y_coin_basDroite - rect.y;
            }
            switch (briques[i][j].id) {
                case 1 :
                    SDL_RenderCopy(renderer, brique_1coup, NULL, &rect);
                    break;
                case 2:
                    SDL_RenderCopy(renderer, brique_2coup, NULL, &rect);
                    break;
                case 3:
                    SDL_RenderCopy(renderer, brique_metal, NULL, &rect);
                    break;
                case 4 :
                    SDL_RenderCopy(renderer, brique_powerup, NULL, &rect);
                    break;
                case 5 :
                    SDL_RenderCopy(renderer, brique_TNT, NULL, &rect);
                    break;
                case 6 :
                    SDL_RenderCopy(renderer, brique_reverse, NULL, &rect);
                    break;
                case 7 :
                    SDL_RenderCopy(renderer, brique_bonus, NULL, &rect);
                    break;
                default :
                    break;
            }

            // on génére les powerups s'il y en a
            if(briques[i][j].pw_up > 0){
                rect.x = briques[i][j].pwup_posx- TAILLEPWUP;
                rect.y = briques[i][j].pwup_posy- TAILLEPWUP;;
                rect.w = 2 * TAILLEPWUP;
                rect.h = 2 * TAILLEPWUP;
                switch (briques[i][j].pw_up) {
                    case 1 :
                        SDL_RenderCopy(renderer, retrecissement, NULL, &rect);
                        break;
                    case 2:
                        SDL_RenderCopy(renderer, reverse, NULL, &rect);
                        break;
                    case 3:
                        SDL_RenderCopy(renderer, perte_piece, NULL, &rect);
                        break;
                    case 4:
                        SDL_RenderCopy(renderer, balle_rapide, NULL, &rect);
                        break;
                    case 5 :
                        SDL_RenderCopy(renderer, agrandissement, NULL, &rect);
                        break;
                    case 6 :
                        SDL_RenderCopy(renderer, aimant, NULL, &rect);
                        break;
                    case 7 :
                        SDL_RenderCopy(renderer, explosif, NULL, &rect);
                        break;
                    case 8 :
                        SDL_RenderCopy(renderer, multi_piece, NULL, &rect);
                        break;
                    case 9 :
                        SDL_RenderCopy(renderer, ajout_vie, NULL, &rect);
                        break;
                    default :
                        break;
                }
            }
        }
    }
    // on génère la barre mtn, on prend que la taille standard pour l'instant il faudra faire un switch pour plus tard
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
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
    for(int i = 0 ; i<9; i++){
        desactiverPWUP(i);
    }
    if(niveaufini) {
        if(niveau>0) {
            Mix_PlayChannel(-1, fin_niveau, 0);
        }
        genererTableau();
        vies++;
        niveau++;
    }
    reinitCollision(NbBriqueLongueur+1,NbBriqueHauteur+1);
}