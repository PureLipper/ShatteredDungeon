//
// Created by 林炜昊 on 2023/11/13.
//

#include <ctime>
#include "Entity.h"
#include "tools/Usages.h"
#include "launch/GameCore.h"
#include "tools/Log.h"

std::default_random_engine &Entity::RE = *new std::default_random_engine(time(nullptr));

const std::vector<std::vector<IMAGE>> &Entity::getAnim() const {
    return anim;
}

void Entity::gainIntent(const Point& target) {
    intent = BFSRoadFinding(pos,target);
}

void Entity::act() {
    GameCore *gm = GameCore::getGameCore();
    if(!intent.empty()) {
        gm->getMaps().at(gm->getFloorNow()).moveEntity(this, intent.back());
        this->pos = Point(intent.back());
        intent.pop_back();
    }
}

const Point &Entity::getPos() const {
    return pos;
}

void Entity::setPos(const Point &p) {
    pos = p;
}

int Entity::getHealthNow() const {
    return health_now;
}

int Entity::getVision() const {
    return vision;
}
