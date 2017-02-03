#pragma once

#include "common.h"

#include <vector>
#include <set>
#include <iostream>


template<class T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& v)
{
    for (const T& item: v) {
        os << item << " ";
    }
    os << std::endl;
    return os;
}


std::ostream& operator<<(std::ostream& os, const Point& p);

template<class T>
std::ostream& operator<<(std::ostream& os, std::vector<T>& v)
{
    for (const T& item: v) {
        os << item << " ";
    }
    os << std::endl;
    return os;
}
