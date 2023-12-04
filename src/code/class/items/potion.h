//
// Created by 林炜昊 on 2023/11/14.
//
#pragma once

#include "items/Item.h"

class potion : public Item{
public:
    virtual void use() = 0;

};