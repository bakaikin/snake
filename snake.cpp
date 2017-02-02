#include "snake.h"
#include "common.h"


std::vector<Point> Snake::body() const
{
    std::vector<Point> result;
    result.push_back(head_);
    for (Direction where: body_) {
        result.push_back(result.back() - where);
    }
    return result;
}

void Snake::move(Direction where)
{
    head_ = head_ + where;
    body_.insert(body_.begin(), where);
    if (food_ > 0) {
        --food_;
    } else {
        body_.pop_back();
    }
}
