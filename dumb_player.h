#include "player.h"


class DumbPlayer: public Player {
public:
    DumbPlayer(int index, Direction where)
    : Player(index), where_(where) {}

    virtual Direction makeTurn(const Field& field)
    {
        return where_;
    }

private:
    Direction where_;
};
