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

bool pasDeBriqueInvincibleACote(unsigned short i,unsigned short j){
    bool retour = true;
    unsigned short limiteIJ[4];
    if(i>0){
        limiteIJ[0] = i-1;
    }
    else{
        limiteIJ[0] = i;
    }
    if(i < NbBriqueLongueur + 1){
        limiteIJ[1] = i+1;
    }
    else{
        limiteIJ[1] = i;
    }
    if(j>0){
        limiteIJ[2] = j-1;
    }
    else{
        limiteIJ[2] = j;
    }
    if(j < NbBriqueHauteur + 1){
        limiteIJ[3] = j+1;
    }
    else{
        limiteIJ[3] = j;
    }
    for(unsigned short i2= limiteIJ[0]; i2<limiteIJ[1];i2++){
        for(unsigned short j2 = limiteIJ[2];j2<limiteIJ[3];j2++){
            if(briques[i2][j2].id == 3 && ( !((i2 == i) && (j2 == j)) ) ){
                retour = false;
            }
        }
    }
    return retour;
}

void genererTableau(){
    for(unsigned short i = 0; i < NbBriqueLongueur; i++){
        for(unsigned short  j = 0; j < NbBriqueHauteur; j++) {
            briques[i][j].id = 0;
        }
    }
    unsigned short nbGenere;
    unsigned char id;
    for(unsigned short i = 0; i < NbBriqueLongueur; i++){
        for(unsigned short  j = 0; j < NbBriqueHauteur; j++){
            nbGenere = rand()%1000;
            if(nbGenere<750){
                id = 1; // 75% de générer une brique normale
            }
            else if(nbGenere<900){
                id = 2; // 15% de générer une brique double
            }
            else if(nbGenere<980 && pasDeBriqueInvincibleACote(i,j)){
                id = 3; // +- 8% de générer une brique invincible
            }
            else if (nbGenere<980){
                id = 1; // on génère une brique normale si on peut pas faire une invincible
            }
            else if(nbGenere<990){
                id = 5; // 1% de générer une brique explosive
            }
            else if(nbGenere<993){
                id = 6; // 0.3% de générer une brique toxique
            }
            else{
                id = 7; // 0.7% de générer une brique faveur
            }
            briques[i][j].id = id;
            donnerCoords(&briques[i][j],i, j);
        }
    }

}


void afficheTab(){
    for (int j = 0; j < NbBriqueHauteur; j++) {
        for (int i = 0; i < NbBriqueLongueur; i++) {
            printf("%hu",briques[i][j].id);
        }
        printf("\n");
    }
    printf("\n\n");
}


