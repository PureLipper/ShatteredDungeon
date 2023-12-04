#pragma once

#include"launch/GameWindow.h"
#include "Point.h"
#include "items/Item.h"
#include "items/ItemStack.h"
#include "entity/Entity.h"
#include <iostream>
#include<random>
#include<ctime>

class Map {

private:
    Point upFloorPoint;
    Point downFloorPoint;
    unsigned int length;
    unsigned int width;
    unsigned int **map;
    unsigned int **maskMap;
    unsigned int **inSight;
    Entity ***entityMap;
    std::vector<ItemStack> **itemOnMap;

public:
    static IMAGE *pics;
    static IMAGE *shadePics;
    void updateEntity();

    Entity *getEntity(const Point &p,int dx = 0,int dy = 0) const;

    void setEntity(const Point &p,Entity *e) const;

    void moveEntity(Entity *target, const Point &to) const;

    std::vector<ItemStack> &getItemStacksOn(Point p) const;

    unsigned int **getInSight() const;

    void addItemTo(ItemStack &itemstack, const Point &p) const;

    const Point &getUpFloorPoint() const;

    void setUpFloorPoint(const Point &p);

    const Point &getDownFloorPoint() const;

    void setDownFloorPoint(const Point &p);

    unsigned int **getMaskMap() const;

    //‘§º”‘ÿÃ˘Õº◊ ‘¥
    static void preloadRes();

    Map(unsigned int l, unsigned int w);

    void drawMapTo(IMAGE* dst) const;

    void setPointValue(unsigned int x, unsigned int y, unsigned int value, unsigned int dx = 0, unsigned int dy = 0);

    void setPointValue(const Point &p, unsigned int value, unsigned int dx = 0, unsigned int dy = 0);

    void show() const;

    void showInSight() const;

    void showMaskMap() const;

    unsigned int getLength() const;

    void setLength(unsigned int l);

    unsigned int getWidth() const;

    void setWidth(unsigned int w);

    unsigned int **getMap() const;

    unsigned int getPointValue(const Point &p, int dx = 0, int dy = 0) const;

    unsigned int getPointValue(int x, int y) const;

    void restoreInSight() const;
};

