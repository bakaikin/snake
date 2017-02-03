#pragma once

#include <climits>


enum Direction { UP, RIGHT, DOWN, LEFT };

enum FieldType {
    NOTHING = 0,
    CHERRY = 21,
    LIFE = 25,
    BOMB = 666,
    SNAKE = 99,
    WALL = 100
};

class Point {
public:
    Point(int ix = INT_MAX, int iy = INT_MAX)
    : x_(ix), y_(iy) {}

    int x() const { return x_; }
    int y() const { return y_; }

private:
    int x_;
    int y_;
};

bool operator==(const Point& lhs, const Point& rhs);

Point operator-(const Point& point, Direction where);
Point operator+(const Point& point, Direction where);
