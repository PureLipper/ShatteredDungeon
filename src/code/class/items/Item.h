//
// Created by 林炜昊 on 2023/11/13.
//
#pragma once

#include <easyx.h>
#include <string>
#include "map/Point.h"

class Item {
protected:
    IMAGE *avatar = new IMAGE();
public:
    virtual ~Item() = default;

    IMAGE *getAvatar() const;

    static void preloadRes();
    static IMAGE *itemImage;
};