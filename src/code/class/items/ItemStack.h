//
// Created by 林炜昊 on 2023/11/16.
//

#pragma once

#include "Item.h"

class ItemStack {
private:
    Item item;
    int count = 0;
public:
    Item &getItem();

    void setItem(const Item &i);

    ItemStack(const Item &item, int count);

    int getCount() const;

    void setCount(int i);

    void countUp(int i = 1);

    void countDown(int i = 1);
};
