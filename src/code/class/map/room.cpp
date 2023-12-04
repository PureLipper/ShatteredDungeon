#include "room.h"

const int room::_LIBRARY[7][6] = {BOOKSHELF,	BOOKSHELF,	BOOKSHELF,	BOOKSHELF,	BOOKSHELF,	BOOKSHELF,
								  BOOKSHELF,	WOODEN_FLOOR,	WOODEN_FLOOR,	WOODEN_FLOOR,	WOODEN_FLOOR,	BOOKSHELF,
								  BOOKSHELF,	WOODEN_FLOOR,	WOODEN_FLOOR,	WOODEN_FLOOR,	WOODEN_FLOOR,	BOOKSHELF,
								  BOOKSHELF,	WOODEN_FLOOR,	WOODEN_FLOOR,	STAGE,		WOODEN_FLOOR,	BOOKSHELF,
								  BOOKSHELF,	WOODEN_FLOOR,	WOODEN_FLOOR,	WOODEN_FLOOR,	WOODEN_FLOOR,	BOOKSHELF,
								  BOOKSHELF,	WOODEN_FLOOR,	WOODEN_FLOOR,	WOODEN_FLOOR,	WOODEN_FLOOR,	BOOKSHELF,
								  BOOKSHELF,	BOOKSHELF,	BOOKSHELF,	BOOKSHELF,	BOOKSHELF,	BOOKSHELF};
const int room::_HEALTH_WELL[4][3] = {FLOOR,	FLOOR,          FLOOR,
									  FLOOR,	HEALTH_WELL,    FLOOR,
									  FLOOR,	FLOOR,          FLOOR,
									  FLOOR,	FLOOR,          FLOOR};

room::room(Point *p1, Point *p2) {
    p[0].setX(p1->getX());
    p[0].setY(p1->getY());
    p[1].setX(p2->getX());
    p[1].setY(p1->getY());
    p[2].setX(p2->getX());
    p[2].setY(p2->getY());
    p[3].setX(p1->getX());
    p[3].setY(p2->getY());
    length = p[2].getX()-p[0].getX() - 1;
    width = p[2].getY()-p[0].getY() - 1;
}

const Point *room::getPoints() const {
    return p;
}

const std::vector<Point>& room::getDoor()  {
    return door;
}

void room::setDoor(const std::vector<Point> &d) {
    room::door = d;
}

void room::addDoor(Point &pt) {
    door.push_back(pt);
}

room::room(const room &r) = default;

int room::getTag() const {
    return tag;
}

void room::setTag(int tag) {
    room::tag = tag;
}

unsigned int room::getLength() const {
    return length;
}

void room::setLength(unsigned int length) {
    room::length = length;
}

unsigned int room::getWidth() const {
    return width;
}

void room::setWidth(unsigned int width) {
    room::width = width;
}
