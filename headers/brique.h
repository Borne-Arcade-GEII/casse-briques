//
// Created by Nathan on 23/01/2023.
//

#ifndef CASSE_BRIQUES_BRIQUE_H
#define CASSE_BRIQUES_BRIQUE_H
#define TAILLEPWUP 10
#define VITESSE_CHUTE_PWP 0.05

struct brique {
    unsigned char id ;
    unsigned short x_coin_hautGauche;
    unsigned short y_coin_hautGauche;
    unsigned short x_coin_basDroite;
    unsigned short y_coin_basDroite;
    unsigned char pw_up ; // les ID de powerup vont de 1 à 9 : 1.2.3.4 = malus 5.6.7.8.9 = bonus
    float pwup_posx;
    float pwup_posy;
    float pwup_vitesse_chute; //vitesse de chute
};

typedef struct brique brique;
void donnerCoords(brique *brique, unsigned short posx, unsigned short posy);// remplit les coordonnées xy de la brique
void casseLaBrique(brique *brique, int i, int j);
void generePowerup(brique *brique , char type);//génere un powerup parmi 2 types : '?' = malus et bonus; '+' = bonus seulement
void updatePowerup();
void gereCollisionPwBord(brique *brique1);
void gereCollisionPwBarre(brique *brique1);
void activerPwUp(brique *brique1);
//en fonction de la position de la brique dans le tableau
#endif //CASSE_BRIQUES_BRIQUE_H
