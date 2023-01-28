//
// Created by Nathan on 24/01/2023.
//
#include "../headers/balle.h"
#include "../headers/main.h"
#include "../headers/tableau.h"
#include "../headers/vies.h"

balle balle1 = {0,0,0,0,0,0,0,true,false};

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
        reinitCollision(NbBriqueLongueur+1,NbBriqueHauteur+1);
    }
    if (b->posy < b->rayon){
        b->vitessey = -b->vitessey;
        reinitCollision(NbBriqueLongueur+1,NbBriqueHauteur+1);
    }
    if(b->posy > ScrHeight - b->rayon){
        if(vies>0) {
            vies--;
            reset(false);
        }
    }
}

void gereCollisionBarre(balle *b){

    if(b->posx > barre1.posCentre-barre1.Longueur && b->posx < barre1.posCentre+barre1.Longueur){
        if(b->posy > barre1.positionyBarre - barre1.Hauteur && b-> posy < barre1.positionyBarre + barre1.Hauteur ) {
            if(barre1.magnetique >0){
                b->freeze = true;
            }
            float calc_inter = (b->posx - barre1.posCentre + barre1.Longueur);
            float angle = (-calc_inter / (2 * barre1.Longueur)) * (90) +140;
            // on génère un angle entre 40 et 140 degrés en fonction de la position de la balle sur la barre
            b->angle = angleDegreVersRadian(angle);
            calculVitesseRect(b);
            reinitCollision(NbBriqueLongueur+1,NbBriqueHauteur+1);
        }
    }
}

void gereCollisionBrique(balle *b){
    //on teste pour chaque brique s'il y a collisiond
    for(int i = 0 ; i<NbBriqueLongueur;i++) {
        for (int j = 0; j < NbBriqueHauteur; j++) {
            if (b->posx + b->rayon > briques[i][j].x_coin_hautGauche && b->posx - b->rayon < briques[i][j].x_coin_basDroite) {
                if (b->posy + b->rayon > briques[i][j].y_coin_hautGauche && b->posy - b->rayon < briques[i][j].y_coin_basDroite) {
                    if(briques[i][j].id > 0 && !briques[i][j].collision) {

                        bool cond_a = (b->posx < briques[i][j].x_coin_hautGauche + b->rayon) ||
                                 (b->posx >briques[i][j].x_coin_basDroite -b->rayon);
                        bool cond_b = (b->posy < briques[i][j].y_coin_hautGauche + b->rayon) ||
                                      (b->posy >briques[i][j].y_coin_basDroite -b->rayon);

                        // faut modifier la fonction pour faire en sorte que la modif de vitesse en coin ne s'applique que quand t'as pas de briques a coté du coin

                        if(cond_a && cond_b){// dans les coins
                            float xrelatif = b->posx - briques[i][j].x_centre;
                            float yrelatif =  briques[i][j].y_centre - b->posy;//faut inverser comme les coords y sont calcules a l'envers
                            b->angle = atan(yrelatif/xrelatif);
                            if(xrelatif<0){
                                b->angle += M_PI;
                            }

                            printf("%f %f %f\n",xrelatif,yrelatif,b->angle);
                            calculVitesseRect(b);
                        }
                        else if(cond_a) {// si on touche la brique sur le côté gauche droit
                                b->vitessex = -b->vitessex;
                            }
                        else if(cond_b){// si on touche la brique sur le côté haut bas
                            b->vitessey = -b->vitessey;
                        }
                        briques[i][j].collision = true;
                        reinitCollision(i,j);
                        casseLaBrique(&briques[i][j],i,j);
                    }
                }
            }
        }
    }
}