//
// Created by 林炜昊 on 2023/11/11.
//

#include "Mage.h"

void Mage::loadImages() {
    const CHAR* t = R"(src\image\character\mage.png)";
    Player::preloadImages(t);
}

Mage::Mage() = default;
