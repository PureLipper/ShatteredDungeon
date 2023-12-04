#pragma once

#include <vector>
#include "Point.h"
#include "attr.h"

class room {
public:
    static const int _LIBRARY[7][6];
	static const int _HEALTH_WELL[4][3];
public:
	room(Point *p1, Point *p2);

    room(const room &r);

    const Point *getPoints() const;

public:
    const std::vector<Point>& getDoor() ;

    void addDoor(Point& pt);

    void setDoor(const std::vector<Point> &d);

    int getTag() const;

    void setTag(int tag);

private:
    //内长
    unsigned int length;
    //内宽
    unsigned int width;
public:
    unsigned int getLength() const;

    void setLength(unsigned int length);

    unsigned int getWidth() const;

    void setWidth(unsigned int width);

private:
    int tag = _NULL;
    std::vector<Point> door;
    Point p[4];//0是左上，1是右上，2是右下，3是左下

};

