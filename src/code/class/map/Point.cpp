#include "Point.h"
int Point::getX() const {
	return x;
}
int Point::getY() const {
	return y;
}
void Point::setX(int X) {
	x = X;
}
void Point::setY(int Y) {
	y = Y;
}

bool Point::operator==(const Point &p) const {
    if(this->x == p.x && this->y == p.y) return true;
    else return false;
}

Point Point::operator-(Point &p) const {
    return {this->x-p.x,this->y-p.y};
}

Point Point::operator+(Point &p) const {
    return {this->x+p.x,this->y+p.y};
}

bool Point::operator!=(const Point &p) const {
    if(this->x != p.x || this->y != p.y) return true;
    else return false;
}

Point::Point(const Point &p, int dx, int dy) {
    this->x = p.x + dx;
    this->y = p.y + dy;
}