#include "common.h"


bool operator==(const Point& lhs, const Point& rhs)
{
    return lhs.x() == rhs.x() && lhs.y() == rhs.y();
}

Point operator-(const Point& point, Direction where)
{
    switch (where) {
        case UP:
            return Point(point.x(), point.y() - 1);
        case RIGHT:
            return Point(point.x() - 1, point.y());
        case DOWN:
            return Point(point.x(), point.y() + 1);
        case LEFT:
            return Point(point.x() + 1, point.y());
    }
    throw std::logic_error("<censored>");
}

Point operator+(const Point& point, Direction where)
{
    return point - static_cast<Direction>((where + 2) % 4);
}
