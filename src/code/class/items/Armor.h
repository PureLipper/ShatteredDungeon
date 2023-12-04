//
// Created by 林炜昊 on 2023/11/13.
//
#pragma once

#include "items/Item.h"

class Armor : public Item{
protected:
    int upgradeLevel = 0;
    int tier = 0;
    int baseDef = 0;
    int defRange = 0;
    int requiredStrength = 0;
public:
    int getUpgradeLevel() const;

    int getTier() const;

    int getBaseDef() const;

    int getDefRange() const;

    int getRequiredStrength() const;
};