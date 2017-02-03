#include "field.h"


Field::Field(
    const std::vector<std::vector<FieldType>>& pattern,
    std::map<int, Snake> snakes,
    const std::vector<FieldObject>& cherries,
    const std::vector<FieldObject>& lives,
    const std::vector<FieldObject>& bombs)
: data_(pattern)
, snakes_(snakes)
, cherries_(cherries)
, lives_(lives)
, bombs_(bombs)
{
    for (auto item: snakes) {
        std::vector<Point> body = item.second.body();
        for (int j = 0; j < body.size(); ++j) {
            // If the point is invalid and does not belong to the field, skip it. The snake will die this turn.
            // FIXME: do something with this hack
            if (body[j].x() < 0 ||
                body[j].x() >= width() ||
                body[j].y() < 0 ||
                body[j].y() >= height()) {

                continue;
            }

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
