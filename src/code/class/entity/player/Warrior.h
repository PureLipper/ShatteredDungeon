//
// Created by 林炜昊 on 2023/11/11.
//
#pragma once

#include "entity/Player.h"

class Warrior : public Player {

public:
    Warrior();

    void loadImages() override;
};