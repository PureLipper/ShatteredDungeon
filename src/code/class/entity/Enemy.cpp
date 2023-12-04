//
// Created by 林炜昊 on 2023/11/16.
//

#include "Enemy.h"
#include "launch/GameCore.h"
#include "tools/Usages.h"

void Enemy::attacked(int damage) {
    if(health_now - damage <= 0){
        health_now = 0;
        die();
    }else{
        health_now -= damage;
    }
    /*TODO
     * 伤害显示*/
}

void Enemy::attack(Player &player) {
    std::uniform_int_distribution<int> uid(baseDamage,baseDamage+damageRange);
    player.attacked(uid(RE));
    /*TODO
     * 攻击动画*/
}

void Enemy::die() {
    GameCore::getGameCore()->getMaps().at(GameCore::getGameCore()->getFloorNow()).setEntity(pos,nullptr);
    delete this;
}

void Enemy::decide() {
    if(LookingForTarget(this)){
        status = MOVING;
    }else{

    }
}

