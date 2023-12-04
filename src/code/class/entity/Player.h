//
// Created by ÁÖì¿ê» on 2023/11/6.
//

#pragma once

#include <string>
#include <easyx.h>
#include <vector>
#include <random>
#include "map/Point.h"
#include "attr.h"
#include "items/Item.h"
#include "entity/Entity.h"
#include "items/armor/ClothArmor.h"
#include "items/Weapon.h"
#include "items/Artifact.h"
#include "items/Ring.h"
#include "items/weapon/meleeWeapon/WornShortsword.h"
#include "items/ItemStack.h"
#include "Enemy.h"
class Enemy;
class Player : public Entity {
private:
    int level = 0;
    double speed = 1.0;
    int status = WATCHING;
    std::vector<ItemStack> Backpack;
protected:
    int handDamage;
    int handDamageRange;
    Armor *pArmor = new ClothArmor();
    Weapon *pWeapon = nullptr;
    Artifact *pArtifact;
    Ring *pRing[2];

public:
    void act() override;

    double getSpeed() const;

    void setSpeed(double s);

    void preloadImages(const CHAR* src);

    void FlipHorizontal();

    int getFaceDirection() const;

    void setFaceDirection(int faceDirection);

    int getStatus() const;

    void setStatus(int s);

    int getLevel() const;

    void levelUp();

    int getHealthNow() const;

    void setHealthNow(int healthNow);

    int getMaxHealth() const;

    void setMaxHealth(int maxHealth);

    void upward();

    void downward();

    void leftward();

    void rightward();

    void draw(int frame) override;

    void watching();

    void unlocking();

    void gainVision();

    void wearUp(Armor &armor);

    void wearUp(Weapon &weapon);

    void cast(Point &target,int stackPos);

    void drop(int stackPos);

    void pickUp();

    void openDoor();

    void closeDoor();

    void attack(Enemy &enemy);

    void attacked(int damage);
};