//
// Created by 林炜昊 on 2023/11/13.
//

#include "ScaleArmor.h"

ScaleArmor::ScaleArmor() {
    SetWorkingImage(itemImage);
    getimage(avatar,47,176,16,13);
    Armor::upgradeLevel = 0;
    Armor::baseDef = 0;
    Armor::defRange = 9;
    Armor::tier = 4;
    Armor::requiredStrength = 16;
    SetWorkingImage();
}