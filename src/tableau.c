//
// Created by Nathan on 20/01/2023.
//
#include "../headers/tableau.h"
#include "../headers/brique.h"
#include "../headers/main.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

brique briques[NbBriqueLongueur][NbBriqueHauteur] ;

limites defLimites(int i, int j){
    limites retour;
    if(i>0){
        retour.limA = i-1;
    }
    else{
        retour.limA  = i;
    }
    if(i < NbBriqueLongueur - 1){
        retour.limB  = i+1;
    }
    else{
        retour.limB  = i;
    }
    if(j>0){
        retour.limC = j-1;
    }
    else{
        retour.limC = j;
    }
    if(j < NbBriqueHauteur - 1){
        retour.limD = j+1;
    }
    else{
        retour.limD = j;
    }
    return retour;
}

bool pasDeBriqueInvincibleACote(unsigned short i,unsigned short j){
    bool retour = true;
    limites limiteIJ = defLimites(i,j);
    for(unsigned short i2= limiteIJ.limA; i2<=limiteIJ.limB;i2++){
        for(unsigned short j2 = limiteIJ.limC;j2<=limiteIJ.limD;j2++){
            if(briques[i2][j2].id == 3 && ( !((i2 == i) && (j2 == j)) ) ){
                retour = false;
            }
        }
    }
    return retour;
}

void explosionBrique(unsigned short i,unsigned short j){
    if(briques[i][j].id != 3) {
        char explose = 0 ;
        limites limiteIJ = defLimites(i, j);
        for (unsigned short i2 = limiteIJ.limA; i2 <= limiteIJ.limB; i2++) {
            for (unsigned short j2 = limiteIJ.limC; j2 <= limiteIJ.limD; j2++) {
                if (briques[i2][j2].id != 3) {
                    casseLaBrique(&briques[i2][j2], i2, j2,true);
                    explose = 1;
                }
            }
        }
        if(explose){
            Mix_PlayChannel(-1, brique_explose, 0);
        }
    } else{
        Mix_PlayChannel(-1, brique_cassee3, 0);
    }
}

void genererTableau(){
    for(unsigned short i = 0; i < NbBriqueLongueur; i++){
        for(unsigned short  j = 0; j < NbBriqueHauteur; j++) {
            briques[i][j].id = 0;
            briques[i][j].pw_up = 0;
        }
    }
    unsigned short nbGenere;
    unsigned char id;
    for(unsigned short i = 0; i < NbBriqueLongueur; i++){
        for(unsigned short  j = 0; j < NbBriqueHauteur; j++){
            nbGenere = rand()%1000;
            if(nbGenere<700){
                id = 1; // 70% de générer une brique normale
            }
            else if(nbGenere<850){
                id = 2; // 15% de générer une brique double
            }
            else if(nbGenere<930 && pasDeBriqueInvincibleACote(i,j)){
                id = 3; // +- 8% de générer une brique invincible
            }
            else if (nbGenere<930){
                id = 1; // on génère une brique normale si on peut pas faire une invincible
            }

            else if(nbGenere<960){
                id = 4; // 3% de générer une brique à bonus
            }
            else if(nbGenere<980){
                id = 5; // 3% de générer une brique explosive
            }
            else if(nbGenere<990){
                id = 6; // 1% de générer une brique toxique
            }
            else{
                id = 7; // 1% de générer une brique faveur
            }
            briques[i][j].id = id;
            donnerCoords(&briques[i][j],i, j);
        }
    }

}

bool tableauFini(){
    bool retour = true;
    for(unsigned short i = 0; i < NbBriqueLongueur; i++){
        for(unsigned short  j = 0; j < NbBriqueHauteur; j++){
            if(briques[i][j].id == 0 || briques[i][j].id == 3){
            }else{
                retour = false;
            }
        }
        }
    return retour;
}

void reinitCollision(unsigned short i, unsigned short j){
    for(unsigned short i2 = 0; i2 < NbBriqueLongueur; i2++){
        for(unsigned short  j2 = 0; j2 < NbBriqueHauteur; j2++) {
            if(!(i == i2 && j == j2)){
                briques[i2][j2].collision = false;
            }
        }
    }
}

