//
// Created by 林炜昊 on 2023/11/16.
//

#include "ThrowingWeapon.h"

void ThrowingWeapon::setEnduranceNow(int enduranceNow) {
    endurance_now = enduranceNow;
}

void ThrowingWeapon::enduranceDown() {
    endurance_now--;
}

int ThrowingWeapon::getEnduranceNow() const {
    return endurance_now;
}

int ThrowingWeapon::getMaxEndurance() const {
    return maxEndurance;
}
