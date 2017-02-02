#include "field.h"


Field::Field(
    const vector<vector<FieldType>>& pattern,
    map<int, Snake> snakes,
    const vector<FieldObject>& cherries,
    const vector<FieldObject>& lives,
    const vector<FieldObject>& bombs)
: data_(pattern)
, snakes_(snakes)
, cherries_(cherries)
, lives_(lives)
, bombs_(bombs)
{
    for (int i = 0; i < snakes.size(); ++i) {
        vector<Point> body = snakes[i].body();
        for (int j = 0; j < body.size(); ++j) {
            setPoint(body[j], SNAKE);
        }
    }

    for (int i = 0; i < cherries.size(); ++i) {
        setPoint(cherries[i].point(), CHERRY);
    }

    for (int i = 0; i < lives.size(); ++i) {
        setPoint(lives[i].point(), LIFE);
    }

    for (int i = 0; i < bombs.size(); ++i) {
        setPoint(bombs[i].point(), BOMB);
    }
}

char asSymbol(FieldType fieldType)
{
    switch (fieldType)
    {
        case NOTHING:
            return ' ';
        case CHERRY:
            return 'c';
        case LIFE:
            return 'l';
        case BOMB:
            return 'B';
        case SNAKE:
            return 's';
        case WALL:
            return '#';
        default:
            throw std::runtime_error("Unknown field type");
    }
    // this can't happen
    return '+';
}

std::ostream& operator<<(std::ostream& os, const Field& field)
{
    for (int i = 0; i < field.width() + 2; ++i) {
        os << '#';
    }
    os << std::endl;

    for (int i = 0; i < field.height(); ++i) {
        os << '#';
        for (int j = 0; j < field.width(); ++j) {
            os << asSymbol(field.at(j, i));
        }
        os << '#' << std::endl;
    }

    for (int i = 0; i < field.width() + 2; ++i) {
        os << '#';
    }
    os << std::endl;

    return os;
}
