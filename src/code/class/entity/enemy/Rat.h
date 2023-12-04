//
// Created by 林炜昊 on 2023/11/16.
//

#pragma once

#include <vector>
#include <easyx.h>
#include "entity/Enemy.h"

class Rat : public Enemy{
    static std::vector<std::vector<IMAGE>>* anim;
public:
    Rat();

    void loadImages() override;

    void draw(int frame) override;
};
