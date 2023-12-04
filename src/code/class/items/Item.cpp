//
// Created by 林炜昊 on 2023/11/13.
//

#include "Item.h"

IMAGE *Item::itemImage = new IMAGE();

void Item::preloadRes() {
    loadimage(itemImage,_T("src\\image\\item\\items.png"));
}

IMAGE *Item::getAvatar() const {
    return avatar;
}
