#pragma once

#include "common.h"
#include "snake.h"

#include <iostream>
#include <vector>
#include <map>


class FieldObject {
public:
    FieldObject() {}

    FieldObject(int lifetime, const Point& point)
    : location_(point), lifetime_(lifetime), age_(0) {}

    void tick()
    {
        ++age_;
    }

    bool isAlive() const
    {
        return (age_ < lifetime_);
    }

    Point point() const
    {
        return location_;
    }

private:
    Point location_;
    int lifetime_;
    int age_;
};

class Field {
public:
    Field(const std::vector<std::vector<FieldType>>& pattern,
          std::map<int, Snake> snakes,
          const std::vector<FieldObject>& cherries,
          const std::vector<FieldObject>& lives,
          const std::vector<FieldObject>& bombs);

    std::map<int, Snake> snakes() const
    {
        return snakes_;
    }

    friend std::ostream& operator<<(std::ostream& os, const Field& field);

    int height() const
    {
        return data_.size();
    }

    int width() const
    {
        return data_[0].size();
    }

    FieldType at(int x, int y) const
    {
        if (x < 0 || x >= width() || y < 0 || y >= height())
            throw std::runtime_error("Field access violation");

        return data_[y][x];
    }

private:
    void setPoint(const Point& point, FieldType value)
    {
        data_[point.y()][point.x()] = value;
    }

    // complete field state
    std::vector<std::vector<FieldType>> data_;

    // map player -> his snake
    std::map<int, Snake> snakes_;

    // temporary field objects
    const std::vector<FieldObject>& cherries_;
    const std::vector<FieldObject>& lives_;
    const std::vector<FieldObject>& bombs_;
};
