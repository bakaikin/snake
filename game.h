#pragma once

#include "common.h"
#include "player.h"

#include <boost/optional.hpp>

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <algorithm>


struct PlayerState {
public:
    PlayerState() {}
    PlayerState(Player * p, Snake s);

    bool isAlive() const
    {
        return lives > 0;
    }

    Player * player;
    int score;
    int lives;
    Snake snake;
};


class Game {
public:
    Game(const vector<vector<FieldType>>& pattern,
         Player * first,
         Player * second,
         Player * third,
         Player * fourth);

    void move();

    void print() const;

    bool isOver() const;

private:        // methods

    boost::optional<Point> locateFieldObject() const;

    int height() const
    {
        return pattern_.size();
    }

    int width() const
    {
        return pattern_[0].size();
    }

    std::map<int, Snake> snakes(int except = -1) const;

    Field currentField(int except = -1) const;

    void refreshFieldObjects(std::vector<FieldObject>& fieldObjects);

    std::map<int, PlayerState> defaultPlayerStates(
        Player * first, Player * second, Player * third, Player * fourth
    );

private:        // fields

    // walls pattern
    vector<vector<FieldType>> pattern_;

    // Temporary field objects
    std::vector<FieldObject> cherries_;
    std::vector<FieldObject> lives_;
    std::vector<FieldObject> deaths_;

    std::map<int, PlayerState> playerStates_;
};
