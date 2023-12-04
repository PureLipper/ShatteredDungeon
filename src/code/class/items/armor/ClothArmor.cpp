//
// Created by 林炜昊 on 2023/11/13.
//

#include "ClothArmor.h"

ClothArmor::ClothArmor() {
    SetWorkingImage(itemImage);
    getimage(avatar,0,176,15,13);
    Armor::upgradeLevel = 0;
    Armor::baseDef = 0;
    Armor::defRange = 3;
    Armor::tier = 1;
    Armor::requiredStrength = 10;
    SetWorkingImage();
}
