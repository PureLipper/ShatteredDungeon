//
// Created by 林炜昊 on 2023/11/16.
//

#pragma once

#include "items/Weapon.h"

class ThrowingWeapon : public Weapon{
private:
    int endurance_now = 0;
    int maxEndurance = 0;
public:
    int getMaxEndurance() const;

    int getEnduranceNow() const;

    void enduranceDown();

    void setEnduranceNow(int enduranceNow);
};
