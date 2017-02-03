#pragma once

#include "common.h"
#include "snake.h"

#include <iostream>
#include <vector>
#include <map>


using std::vector;
using std::map;


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
    Field(const vector<vector<FieldType>>& pattern,
          map<int, Snake> snakes,
          const vector<FieldObject>& cherries,
          const vector<FieldObject>& lives,
          const vector<FieldObject>& bombs);

    map<int, Snake> snakes() const
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
        return data_[y][x];
    }

private:
    void setPoint(const Point& point, FieldType value)
    {
        //std::cout << "Point: " << point.x() << "," << point.y() << std::endl;
        data_[point.y()][point.x()] = value;
    }

    // complete field state
    vector<vector<FieldType>> data_;

    // map player -> his snake
    map<int, Snake> snakes_;

    // temporary field objects
    const vector<FieldObject>& cherries_;
    const vector<FieldObject>& lives_;
    const vector<FieldObject>& bombs_;
};
