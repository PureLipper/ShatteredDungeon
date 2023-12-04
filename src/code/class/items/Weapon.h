#include "items/Item.h"
#pragma once
//
// Created by 林炜昊 on 2023/11/14.
//
class Weapon : public Item{
private:
    int baseDamage;
    int damageRange;
public:
    int getBaseDamage() const;

    int getDamageRange() const;
};