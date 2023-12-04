//
// Created by 林炜昊 on 2023/11/16.
//

#include "ItemStack.h"

Item &ItemStack::getItem() {
    return item;
}

void ItemStack::setItem(const Item &i) {
    ItemStack::item = i;
}

int ItemStack::getCount() const {
    return count;
}

void ItemStack::setCount(int i) {
    ItemStack::count = i;
}

ItemStack::ItemStack(const Item &item, int count) : item(item), count(count) {}

void ItemStack::countDown(int i) {
    count -= i;
}

void ItemStack::countUp(int i) {
    count += i;
}
