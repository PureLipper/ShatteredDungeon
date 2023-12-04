//
// Created by 林炜昊 on 2023/11/13.
//

#include "PlateArmor.h"

PlateArmor::PlateArmor() {
    SetWorkingImage(itemImage);
    getimage(avatar,63,176,14,13);
    Armor::upgradeLevel = 0;
    Armor::baseDef = 0;
    Armor::defRange = 11;
    Armor::tier = 5;
    Armor::requiredStrength = 18;
    SetWorkingImage();
}
