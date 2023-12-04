//
// Created by ÁÖì¿ê» on 2023/11/11.
//
#include "Warrior.h"

void Warrior::loadImages() {
    const CHAR* t = R"(src\image\character\warrior.png)";
    Player::preloadImages(t);
}

Warrior::Warrior() {
    handDamage = 1;
    handDamageRange = 3;
    vision = 9;
}