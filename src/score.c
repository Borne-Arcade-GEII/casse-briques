//
// Created by Nathan on 23/01/2023.
//

#include <stdbool.h>
#include "../headers/score.h"
signed long score = 0;
bool multipts = false;

void ajoutScore(signed short a){
    if(multipts){
        score+= MULTIPTS*a;
    }
    score+= a;
}