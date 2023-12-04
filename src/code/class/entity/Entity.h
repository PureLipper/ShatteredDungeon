#pragma once
#include <easyx.h>
#include <vector>
#include <random>
#include "map/Point.h"
#include "attr.h"

//
// Created by 林炜昊 on 2023/11/13.
//
class Entity {
protected:
    static std::default_random_engine &RE;
    Point pos;
    std::vector<Point> intent;
    std::vector<std::vector<IMAGE>> anim;
    IMAGE *avatar = new IMAGE();
    int health_now = 30;
    int max_health = 30;
    int faceDirection = RIGHTWARD;
    int vision;

public:
    int getVision() const;

    int getHealthNow() const;

    const Point &getPos() const;

    const std::vector<std::vector<IMAGE>> &getAnim() const;

    virtual void loadImages() = 0;

    virtual void act();

    virtual void draw(int frame) = 0;

    void gainIntent(const Point& target);

    void setPos(const Point &p);

    virtual ~Entity() = default;
};