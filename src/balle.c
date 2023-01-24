//
// Created by Nathan on 24/01/2023.
//
#include "../headers/balle.h"
#include "../headers/main.h"
#include "../headers/tableau.h"

balle balle1 = {0,0,0,0,0,0,0,true};

// Initialise la position et la vitesse de la balle
void initBalle(balle *b, int x, int y,  float vitesse, float angle) {
    b->rayon = (short) (0.015 * ScrHeight) ;
    b->posx = x;
    b->posy = y;
    b->vitesse = vitesse;
    b->angle = angle;
    calculVitesseRect(b);
}

// Met à jour la position de la balle en fonction de sa vitesse
void updateBalle(balle *b) {
    if(b->freeze){
    }else {
        gereCollisionBord(b);
        gereCollisionBarre(b);
        gereCollisionBrique(b);
        b->posx = b->posx + b->vitessex;
        b->posy = b->posy + b->vitessey;
    }
    //gére les collisions de la balle avec les briques
}

void calculVitesseRect(balle *b){
    b->vitessex = b->vitesse * cos(b->angle);
    b->vitessey = - b->vitesse * sin(b->angle);
}

float angleDegreVersRadian(float angleDegre){
   return angleDegre * M_PI / 180.0;
}

void gereCollisionBord(balle *b){
    if (b->posx < b->rayon || (b->posx > ScrWidth - b->rayon)) {
        b->vitessex = -b->vitessex;
    }
    if (b->posy < b->rayon || (b->posy > ScrHeight - b->rayon) ) {
        b->vitessey = -b->vitessey;
    }
}

void gereCollisionBarre(balle *b){

    if(b->posx > barre1.posCentre-barre1.Longueur && b->posx < barre1.posCentre+barre1.Longueur){
        if(b->posy > barre1.positionyBarre - barre1.Hauteur && b-> posy < barre1.positionyBarre + barre1.Hauteur ) {
            if(barre1.magnetique >0){
                b->freeze = true;
            } else {
                float calc_inter = (b->posx - barre1.posCentre + barre1.Longueur);
                float angle = (-calc_inter / (2 * barre1.Longueur)) * (90) +
                              140;// on génère un angle entre 40 et 140 degrés en fonction de la position de la balle sur la barre
                b->angle = angleDegreVersRadian(angle);
                calculVitesseRect(b);
            }
        }
    }
}

void gereCollisionBrique(balle *b){
    //on teste pour chaque brique s'il y a collision
    for(int i = 0 ; i<NbBriqueLongueur;i++) {
        for (int j = 0; j < NbBriqueHauteur; j++) {
            if (b->posx + b->rayon > briques[i][j].x_coin_hautGauche && b->posx - b->rayon < briques[i][j].x_coin_basDroite) {
                if (b->posy + b->rayon > briques[i][j].y_coin_hautGauche && b->posy - b->rayon < briques[i][j].y_coin_basDroite) {
                    if(briques[i][j].id != 0) {
                        if ((b->posx < briques[i][j].x_coin_hautGauche + b->rayon) ||
                        (b->posx >briques[i][j].x_coin_basDroite -b->rayon)) {// si on touche la brique sur le côté quoi
                            b->vitessex = -b->vitessex;
                        } else {
                            b->vitessey = -b->vitessey;
                        }
                        casseLaBrique(&briques[i][j],i,j);
                    }
                }
            }
        }
    }
}