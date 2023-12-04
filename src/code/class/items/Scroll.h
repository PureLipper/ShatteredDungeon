//
// Created by 林炜昊 on 2023/11/15.
//

#pragma once

#include "Item.h"

class Scroll : public Item{
public:
    virtual void use() = 0;
};
