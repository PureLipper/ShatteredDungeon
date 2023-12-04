//
// Created by 林炜昊 on 2023/11/13.
//

#include "LeatherArmor.h"

LeatherArmor::LeatherArmor() {
    SetWorkingImage(itemImage);
    getimage(avatar,15,176,16,13);
    Armor::upgradeLevel = 0;
    Armor::baseDef = 0;
    Armor::defRange = 5;
    Armor::tier = 2;
    Armor::requiredStrength = 12;
    SetWorkingImage();
}
