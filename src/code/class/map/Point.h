#pragma once
class Point
{
private:
	int x = 0;
    int y = 0;
public:
	Point()= default;
	Point(int X, int Y) : x(X), y(Y) {};
    Point(const Point& p,int dx = 0,int dy = 0);
    [[nodiscard]] int getX() const;//nodiscard表示这个函数的返回值不能被忽略
    [[nodiscard]] int getY() const;
	void setX(int X);
	void setY(int Y);
    Point operator + (Point &p) const;
    Point operator - (Point &p) const;
    bool operator == (const Point &p) const;
    bool operator != (const Point &p) const;
};

