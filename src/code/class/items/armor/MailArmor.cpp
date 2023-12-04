//
// Created by 林炜昊 on 2023/11/13.
//

#include "MailArmor.h"

MailArmor::MailArmor() {
    SetWorkingImage(itemImage);
    getimage(avatar,31,176,16,13);
    Armor::upgradeLevel = 0;
    Armor::baseDef = 0;
    Armor::defRange = 7;
    Armor::tier = 3;
    Armor::requiredStrength = 14;
    SetWorkingImage();
}
