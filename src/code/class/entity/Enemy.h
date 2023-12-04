//
// Created by 林炜昊 on 2023/11/16.
//
#pragma once

#include "Entity.h"
#include "Player.h"
class Player;
class Enemy : public Entity{
protected:
    int baseDamage = 0;
    int damageRange = 0;
    int status = SLEEPING;
public:
    void attack(Player &player);
    void attacked(int damage);
    void decide();
    void die();
};