//
// Created by 林炜昊 on 2023/11/6.
//

#include <easyx.h>
#include <thread>
#include "Player.h"
#include "launch/GameCore.h"
#include "items/weapon/ThrowingWeapon.h"
#include "tools/Usages.h"
#include "tools/Log.h"

int Player::getHealthNow() const {
    return health_now;
}

void Player::setHealthNow(int healthNow) {
    health_now = healthNow;
}

int Player::getMaxHealth() const {
    return max_health;
}

void Player::setMaxHealth(int maxHealth) {
    max_health = maxHealth;
}

void Player::upward() {
    gainIntent(Point(pos, 0, -1));
}

void Player::downward() {
    gainIntent(Point(pos, 0, 1));
}

void Player::leftward() {
    if (faceDirection == RIGHTWARD) {
        FlipHorizontal();
        faceDirection = LEFTWARD;
    }
    gainIntent(Point(pos, -1, 0));
}

void Player::rightward() {
    if (faceDirection == LEFTWARD) {
        FlipHorizontal();
        faceDirection = RIGHTWARD;
    }
    gainIntent(Point(pos, 1, 0));
}

int Player::getLevel() const {
    return level;
}

//在当前背景下绘制player
void Player::draw(int frame) {
    drawTransparentToCanvas(pos.getX() * 16, pos.getY() * 16, &anim[status][frame]);
}

void Player::watching() {
    status = WATCHING;
}

void Player::unlocking() {
    status = UNLOCKING;
    std::thread t([this] {
        while (true) {
            if (status != UNLOCKING) break;
            if (time(nullptr) % 4 == 0) {
                draw(0);
            } else if (time(nullptr) % 4 == 2) {
                draw(1);
            }
        }
    });
    t.detach();
}

void Player::levelUp() {
    level++;
}

int Player::getStatus() const {
    return status;
}

void Player::setStatus(int s) {
    Player::status = s;
}

int Player::getFaceDirection() const {
    return faceDirection;
}

void Player::setFaceDirection(int FD) {
    Player::faceDirection = FD;
}

//镜像翻转人物
void Player::FlipHorizontal() {
    auto *dst = new IMAGE(anim.at(0).at(0).getwidth(), anim.at(0).at(0).getheight());
    for (std::vector<IMAGE> &src0: anim) {
        for (IMAGE &src: src0) {
            int w = src.getwidth();        // 获取源图像宽度
            int h = src.getheight();        // 获取源图像高度

            // 获取源图像与目标图像的显示缓冲区地址
            DWORD *s = GetImageBuffer(&src);
            DWORD *d = GetImageBuffer(dst);

            // 左右翻转每一行的像素
            for (int x = 0; x < w; x++)
                for (int y = 0; y < h; y++)
                    d[y * w + w - x] = s[y * w + x];
            src = *dst;
        }
    }
    delete dst;
}

void Player::gainVision() {
    const Map &map = GameCore::getGameCore()->getMaps().at((GameCore::getGameCore()->getFloorNow()));
    unsigned int length = map.getLength();
    unsigned int width = map.getWidth();
    map.restoreInSight();
    for (Point p(pos.getX(), pos.getY());
         p.getX() >= 0 && p.getX() < length && p.getY() >= 0 && p.getY() < width; p.setX(p.getX() + 1), p.setY(
            p.getY() + 1)) {
        for (int i = p.getX();
             ((pos.getX() - i) * (pos.getX() - i) + (pos.getY() - p.getY()) * (pos.getY() - p.getY()) <
              vision * vision) && i >= 0 && i < length && p.getY() >= 0 && p.getY() < width; i++) {
            map.getMaskMap()[i][p.getY()] = KNOWN;
            map.getInSight()[i][p.getY()] = INSIGHT;
            if (map.getPointValue(i, p.getY()) == WALL || map.getPointValue(i, p.getY()) == CLOSED_DOOR) break;
        }
        for (int i = p.getY();
             ((pos.getY() - i) * (pos.getY() - i) + (pos.getX() - p.getX()) * (pos.getX() - p.getX()) <
              vision * vision) && p.getX() >= 0 && p.getX() < length && i >= 0 && i < width; i++) {
            map.getMaskMap()[p.getX()][i] = KNOWN;
            map.getInSight()[p.getX()][i] = INSIGHT;
            if (map.getPointValue(p.getX(), i) == WALL || map.getPointValue(p.getX(), i) == CLOSED_DOOR) break;
        }
        if (map.getPointValue(p) == WALL || map.getPointValue(p) == CLOSED_DOOR) break;
    }
    for (Point p(pos.getX(), pos.getY());
         p.getX() >= 0 && p.getX() < length && p.getY() >= 0 && p.getY() < width; p.setX(p.getX() - 1), p.setY(
            p.getY() + 1)) {
        for (int i = p.getX();
             ((pos.getX() - i) * (pos.getX() - i) + (pos.getY() - p.getY()) * (pos.getY() - p.getY()) <
              vision * vision) && i >= 0 && i < length && p.getY() >= 0 && p.getY() < width; i--) {
            map.getMaskMap()[i][p.getY()] = KNOWN;
            map.getInSight()[i][p.getY()] = INSIGHT;
            if (map.getPointValue(i, p.getY()) == WALL || map.getPointValue(i, p.getY()) == CLOSED_DOOR) break;
        }
        for (int i = p.getY();
             ((pos.getY() - i) * (pos.getY() - i) + (pos.getX() - p.getX()) * (pos.getX() - p.getX()) <
              vision * vision) && p.getX() >= 0 && p.getX() < length && i >= 0 && i < width; i++) {
            map.getMaskMap()[p.getX()][i] = KNOWN;
            map.getInSight()[p.getX()][i] = INSIGHT;
            if (map.getPointValue(p.getX(), i) == WALL || map.getPointValue(p.getX(), i) == CLOSED_DOOR) break;
        }
        if (map.getPointValue(p) == WALL || map.getPointValue(p) == CLOSED_DOOR) break;
    }
    for (Point p(pos.getX(), pos.getY());
         p.getX() >= 0 && p.getX() < length && p.getY() >= 0 && p.getY() < width; p.setX(p.getX() + 1), p.setY(
            p.getY() - 1)) {
        for (int i = p.getX();
             ((pos.getX() - i) * (pos.getX() - i) + (pos.getY() - p.getY()) * (pos.getY() - p.getY()) <
              vision * vision) && i >= 0 && i < length && p.getY() >= 0 && p.getY() < width; i++) {
            map.getMaskMap()[i][p.getY()] = KNOWN;
            map.getInSight()[i][p.getY()] = INSIGHT;
            if (map.getPointValue(i, p.getY()) == WALL || map.getPointValue(i, p.getY()) == CLOSED_DOOR) break;
        }
        for (int i = p.getY();
             ((pos.getY() - i) * (pos.getY() - i) + (pos.getX() - p.getX()) * (pos.getX() - p.getX()) <
              vision * vision) && p.getX() >= 0 && p.getX() < length && i >= 0 && i < width; i--) {
            map.getMaskMap()[p.getX()][i] = KNOWN;
            map.getInSight()[p.getX()][i] = INSIGHT;
            if (map.getPointValue(p.getX(), i) == WALL || map.getPointValue(p.getX(), i) == CLOSED_DOOR) break;
        }
        if (map.getPointValue(p) == WALL || map.getPointValue(p) == CLOSED_DOOR) break;
    }
    for (Point p(pos.getX(), pos.getY());
         p.getX() >= 0 && p.getX() < length && p.getY() >= 0 && p.getY() < width; p.setX(p.getX() - 1), p.setY(
            p.getY() - 1)) {
        for (int i = p.getX();
             ((pos.getX() - i) * (pos.getX() - i) + (pos.getY() - p.getY()) * (pos.getY() - p.getY()) <
              vision * vision) && i >= 0 && i < length && p.getY() >= 0 && p.getY() < width; i--) {
            map.getMaskMap()[i][p.getY()] = KNOWN;
            map.getInSight()[i][p.getY()] = INSIGHT;
            if (map.getPointValue(i, p.getY()) == WALL || map.getPointValue(i, p.getY()) == CLOSED_DOOR) break;
        }
        for (int i = p.getY();
             ((pos.getY() - i) * (pos.getY() - i) + (pos.getX() - p.getX()) * (pos.getX() - p.getX()) <
              vision * vision) && p.getX() >= 0 && p.getX() < length && i >= 0 && i < width; i--) {
            map.getMaskMap()[p.getX()][i] = KNOWN;
            map.getInSight()[p.getX()][i] = INSIGHT;
            if (map.getPointValue(p.getX(), i) == WALL || map.getPointValue(p.getX(), i) == CLOSED_DOOR) break;
        }
        if (map.getPointValue(p) == WALL || map.getPointValue(p) == CLOSED_DOOR) break;
    }
}

void Player::preloadImages(const CHAR *src) {
    auto *tiles = new IMAGE;
    loadimage(tiles, _T(src));
    auto *anim_attacking = new std::vector<IMAGE>(3);
    auto *anim_reading = new std::vector<IMAGE>(3);
    auto *anim_unlocking = new std::vector<IMAGE>(2);
    auto *floating = new std::vector<IMAGE>(1);
    auto *anim_dead = new std::vector<IMAGE>(5);
    auto *anim_moving = new std::vector<IMAGE>(6);
    auto *anim_looking = new std::vector<IMAGE>(2);
    SetWorkingImage(tiles);
    getimage(&anim_looking->at(0), 0, 15 * pArmor->getTier(), 12, 15);
    getimage(&anim_looking->at(1), 12, 15 * pArmor->getTier(), 12, 15);
    anim.push_back(*anim_looking);
    for (int i = 0; i < 6; i++) {
        getimage(&anim_moving->at(i), 24 + 12 * i, 15 * pArmor->getTier(), 12, 15);
    }
    anim.push_back(*anim_moving);
    for (int i = 0; i < 5; i++) {
        getimage(&anim_dead->at(i), 96 + 12 * i, 15 * pArmor->getTier(), 12, 15);
    }
    anim.push_back(*anim_dead);
    getimage(&anim_unlocking->at(0), 192, 15 * pArmor->getTier(), 12, 15);
    getimage(&anim_unlocking->at(1), 204, 15 * pArmor->getTier(), 12, 15);
    anim.push_back(*anim_unlocking);
    getimage(&floating->at(0), 216, 15 * pArmor->getTier(), 12, 15);
    anim.push_back(*floating);
    for (int i = 0; i < 2; i++) {
        getimage(&anim_reading->at(i), 228 + 12 * i, 15 * pArmor->getTier(), 12, 15);
    }
    anim.push_back(*anim_reading);
    for (int i = 0; i < 3; i++) {
        getimage(&anim_attacking->at(i), 156 + 12 * i, 15 * pArmor->getTier(), 12, 15);
    }
    anim.push_back(*anim_attacking);
    *avatar = anim_looking->at(0);
    delete tiles;
    delete anim_looking;
    delete anim_unlocking;
    delete anim_moving;
    delete anim_attacking;
    delete anim_reading;
    delete anim_dead;
    SetWorkingImage();
}

void Player::wearUp(Armor &armor) {
    Armor *t = pArmor;
    pArmor = &armor;
    armor = *t;
}

void Player::wearUp(Weapon &weapon) {
    Weapon *t = pWeapon;
    pWeapon = &weapon;
    weapon = *t;
}

void Player::cast(Point &target, int stackPos) {
    GameCore *game = GameCore::getGameCore();
    Item *item = &Backpack.at(stackPos).getItem();
    //判断item是否是weapon
    auto *throwingWeapon = dynamic_cast<ThrowingWeapon *>(item);
    if (game->getMaps().at(game->getFloorNow()).getEntity(pos) != nullptr) {
        auto *enemy = dynamic_cast<Enemy *>(game->getMaps().at(game->getFloorNow()).getEntity(pos));
        if (throwingWeapon && enemy) {
            enemy->attacked(throwingWeapon->getBaseDamage() + (int) (RE() % throwingWeapon->getDamageRange()));
            throwingWeapon->enduranceDown();
            if (throwingWeapon->getEnduranceNow() == 0) {
                throwingWeapon->setEnduranceNow(throwingWeapon->getMaxEndurance());
            } else {
                auto *t = new ItemStack(Backpack.at(stackPos).getItem(), 1);
                game->getMaps().at(GameCore::getGameCore()->getFloorNow()).addItemTo(*t, target);
                delete t;
            }
        }
    } else {
        auto *t = new ItemStack(Backpack.at(stackPos).getItem(), 1);
        game->getMaps().at(GameCore::getGameCore()->getFloorNow()).addItemTo(*t, target);
        delete t;
    }
    if (Backpack.at(stackPos).getCount() > 1) {
        Backpack.at(stackPos).countDown();
    } else {
        if (throwingWeapon) {
            for (ItemStack &IS: game->getMaps().at(GameCore::getGameCore()->getFloorNow()).getItemStacksOn(target)) {
                if (typeid(IS.getItem()).name() == typeid(item).name()) {
                    dynamic_cast<ThrowingWeapon *>(&IS.getItem())->setEnduranceNow(throwingWeapon->getEnduranceNow());
                }
            }
        }
        Backpack.erase(Backpack.begin() + stackPos);
    }
}

void Player::openDoor() {
    if (GameCore::getGameCore()->getMaps().at(GameCore::getGameCore()->getFloorNow()).getPointValue(pos) ==
        CLOSED_DOOR) {
        GameCore::getGameCore()->getMaps().at(
                GameCore::getGameCore()->getFloorNow()).getMap()[pos.getX()][pos.getY()] = OPENED_DOOR;
    }
}

void Player::closeDoor() {
    if (GameCore::getGameCore()->getMaps().at(GameCore::getGameCore()->getFloorNow()).getPointValue(pos) ==
        OPENED_DOOR) {
        GameCore::getGameCore()->getMaps().at(
                GameCore::getGameCore()->getFloorNow()).getMap()[pos.getX()][pos.getY()] = CLOSED_DOOR;
    }
}

void Player::drop(int stackPos) {
    cast(pos, stackPos);
}

void Player::pickUp() {
    GameCore *game = GameCore::getGameCore();
    std::vector<ItemStack> &v = game->getMaps().at(game->getFloorNow()).getItemStacksOn(pos);
    if (!v.empty()) {
        ItemStack &topItemStack = v.back();
        for (ItemStack &IS: Backpack) {
            if (typeid(IS.getItem()).name() == typeid(topItemStack.getItem()).name()) {
                IS.countUp(topItemStack.getCount());
                v.erase(v.end());
                return;
            }
        }
        if (Backpack.size() == 30) {
            std::string t = typeid(topItemStack.getItem()).name();
            Log::p("system", "你捡起了" + t);
            /*TODO
             * Add Logger Toast*/
            return;
        } else {
            Backpack.push_back(topItemStack);
            v.erase(v.end());
        }
    }
}

void Player::attack(Enemy &enemy) {
    if (pWeapon == nullptr) {
        std::uniform_int_distribution<int> uid(handDamage, handDamage + handDamageRange);
        enemy.attacked(uid(RE));
    } else {
        std::uniform_int_distribution<int> uid(pWeapon->getBaseDamage(),
                                               pWeapon->getBaseDamage() + pWeapon->getDamageRange());
        enemy.attacked(uid(RE));
    }
}

void Player::attacked(int damage) {
    health_now -= damage;
    /*TODO
     * 伤害显示*/
}

double Player::getSpeed() const {
    return speed;
}

void Player::setSpeed(double s) {
    Player::speed = s;
}

void Player::act() {
    Entity::act();
    openDoor();
    gainVision();
    closeDoor();
}
