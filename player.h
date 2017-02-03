#pragma once

#include "common.h"
#include "field.h"

#include <stdexcept>


class Player {
public:
    Player(int index) : index_(index) {}

    virtual Direction makeTurn(const Field& field)
    {
        throw std::runtime_error("Not implemented");
    }

protected:
    Snake mySnake(const Field& field) const
    {
        return field.snakes()[index_];
    }

private:
    int index_;
};
