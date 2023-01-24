//
// Created by Nathan on 24/01/2023.
//

#ifndef CASSE_BRIQUES_BALLE_H
#define CASSE_BRIQUES_BALLE_H
struct balle {
    unsigned short posx;
    unsigned short posy;
    signed short vitx;
    signed short vity;
};
typedef struct balle balle;
extern balle balle1;
#endif //CASSE_BRIQUES_BALLE_H
