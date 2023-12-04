//
// Created by 林炜昊 on 2023/11/16.
//
#include "Rat.h"
#include "tools/Usages.h"

std::vector<std::vector<IMAGE>>* Rat::anim = new std::vector<std::vector<IMAGE>>;
void Rat::loadImages() {
    auto *tiles = new IMAGE();
    loadimage(tiles,_T("src\\image\\Enemy\\Rat.png"));
    SetWorkingImage(tiles);
    auto *anim_sleeping = new std::vector<IMAGE>(2);
    auto *anim_attacking = new std::vector<IMAGE>(4);
    auto *anim_chasing = new std::vector<IMAGE>(5);
    getimage(&anim_sleeping->at(0), 0, 0, 16,
             16);
    getimage(&anim_sleeping->at(1), 16, 0, 16, 16);
    anim->push_back(*anim_sleeping);
    for(int i = 0;i < 5;i++){
        getimage(&anim_chasing->at(i),16*i+96,0,16,16);
    }
    anim->push_back(*anim_chasing);
    for(int i = 0;i < 4;i++){
        getimage(&anim_attacking->at(i),16*i+32,0,16,16);
    }
    anim->push_back(*anim_attacking);
    *avatar = anim_sleeping->at(0);
    delete anim_sleeping;
    delete anim_attacking;
    SetWorkingImage();
}


void Rat::draw(int frame) {
    drawTransparentToCanvas(pos.getX() * 16, pos.getY() * 16, &anim->at(0)[0]);

}

Rat::Rat() {
    health_now = 8;
    max_health = 8;
    baseDamage = 1;
    damageRange = 4;
}
