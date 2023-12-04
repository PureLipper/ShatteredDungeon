//
// Created by 林炜昊 on 2023/11/13.
//
#include "Armor.h"

int Armor::getUpgradeLevel() const {
    return upgradeLevel;
}

int Armor::getTier() const {
    return tier;
}

int Armor::getBaseDef() const {
    return baseDef;
}

int Armor::getDefRange() const {
    return defRange;
}

int Armor::getRequiredStrength() const {
    return requiredStrength;
}
