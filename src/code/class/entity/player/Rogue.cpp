//
// Created by 林炜昊 on 2023/11/11.
//

#include "Rogue.h"

void Rogue::loadImages() {
    const CHAR* t = R"(src\image\character\rogue.png)";
    Player::preloadImages(t);
}

Rogue::Rogue() = default;
