#pragma once

#include "common.h"

#include <vector>


class Snake {
public:
    Snake() {}
    Snake(Point sp, std::vector<Direction> b)
    : head_(sp), body_(b), food_(0) {}

    // Returns the snake body that consists of points. Snake head is in the top.
    std::vector<Point> body() const;

    // Perform a shift in the given direction.
    void move(Direction where);

    void increase(int howMuch)
    {
        food_ += howMuch;
    }

    Point head() const
    {
        return head_;
    }

private:
    Point head_;
    std::vector<Direction> body_;
    int food_;
};
