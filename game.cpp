#include "game.h"
#include "io.h"

#include <set>
#include <cmath>


const double CHERRY_PROBABILITY = 0.1;
const double LIFE_PROBABILITY = 0.01;
const double BOMB_PROBABILITY = 0.05;

const int CHERRY_LIFETIME = 20;
const int LIFE_LIFETIME = 25;
const int BOMB_LIFETIME = 15;

const int CHERRY_LENGTH_BONUS = 2;
const int CHERRY_SCORE_BONUS = 10;

const double EXPECTED_CHERRIES = 3;
const double EXPECTED_LIVES = 0.5;
const double EXPECTED_BOMBS = 0.5;


bool randomEvent(double probability);


PlayerState::PlayerState(Player * p, Snake s, int l)
: player(p)
, score(0)
, lives(l)
, snake(s)
{
}


Game::Game(const std::vector<std::vector<FieldType>>& pattern,
     const std::vector<PlayerState>& startStates,
     int maxTurns)
: pattern_(pattern)
, cherries_()
, lives_()
, deaths_()
, maxTurns_(maxTurns)
{
    //srand(time(NULL));
    srand(57); // Let the random be determined in beta version.

    // Initialize index -> player state map
    for (size_t i = 0; i < startStates.size(); ++i) {
        playerStates_[i] = startStates[i];
    }

    Field field = currentField();

    // FIXME: Rewrite field generation

    // Generate cherries, if any
    int attempts = floor(EXPECTED_CHERRIES / CHERRY_PROBABILITY);
    for (int i = 0; i < attempts; ++i) {
        if (randomEvent(CHERRY_PROBABILITY)) {
            boost::optional<Point> point = locateFieldObject();
            if (!point) // could not find a free cell
                break;

            cherries_.push_back(FieldObject(CHERRY_LIFETIME, *point));
        }
    }

    // Generate lives, if any
    attempts = floor(EXPECTED_LIVES / LIFE_PROBABILITY);
    for (int i = 0; i < attempts; ++i) {
        if (randomEvent(LIFE_PROBABILITY)) {
            boost::optional<Point> point = locateFieldObject();
            if (!point) // could not find a free cell
                break;

            lives_.push_back(FieldObject(LIFE_LIFETIME, *point));
        }
    }

    // Generate bombs, if any
    attempts = floor(EXPECTED_BOMBS / BOMB_PROBABILITY);
    for (int i = 0; i < attempts; ++i) {
        if (randomEvent(BOMB_PROBABILITY)) {
            boost::optional<Point> point = locateFieldObject();
            if (!point) // could not find a free cell
                break;

            deaths_.push_back(FieldObject(BOMB_LIFETIME, *point));
        }
    }
}


void Game::move()
{
    // 1. Generate new field
    Field field = currentField();

    // Snakes that will die this turn.
    std::set<int> corpses;

    // 2. Pass the field to the rest of the players. Wait for their turns.
    std::map<int, Direction> turns;
    for (auto playerState: playerStates_) {
        if (playerState.second.isAlive()) {
            try {
                Direction turn = playerState.second.player->makeTurn(field);
                turns[playerState.first] = turn;
            } catch (...) {
                // If player has thrown a tricky exception, let's kill him!
                corpses.insert(playerState.first);
            }
        }
    }

    // Find new snake heads. Refresh players' snakes.
    std::map<int, Point> heads;
    for (auto turn: turns) {
        Snake& snake = playerStates_[turn.first].snake;
        snake.move(turn.second);
        heads[turn.first] = snake.head();
    }

    // Now snakes are already new, and the field is old.
    for (auto item: snakes()) {
        // New field without current snake
        Field newField = currentField(item.first);
        Point head = item.second.head();

        // Does the snake leave the board?
        if (head.x() < 0 ||
            head.x() >= width() ||
            head.y() < 0 ||
            head.y() >= height()) {

            corpses.insert(item.first);
            continue;
        }

        if (field.at(head.x(), head.y()) == BOMB ||
            field.at(head.x(), head.y()) == WALL ||
            newField.at(head.x(), head.y()) == SNAKE) {

            corpses.insert(item.first);

            // The bomb that exploded must disappear.
            if (field.at(head.x(), head.y()) == BOMB) {
                removeFieldObject(deaths_, head);
            }
        }

        if (field.at(head.x(), head.y()) == CHERRY) { // eat
            playerStates_[item.first].snake.increase(CHERRY_LENGTH_BONUS);
            playerStates_[item.first].score += CHERRY_SCORE_BONUS;

            // remove the cherry if we've eaten it
            removeFieldObject(cherries_, head);
        }

        if (field.at(head.x(), head.y()) == LIFE) { // no support for lives at the moment
            // do nothing
            removeFieldObject(lives_, head);
        }
    }

    // Remove the dead.
    for (int player: corpses) {
        --playerStates_[player].lives;
    }

#ifdef DEBUG
    std::cout << "Corpses this turn: " << corpses << std::endl;
#endif

    // 3. Kill the expired stuff. Generate new stuff in free places.
    refreshFieldObjects(cherries_, CHERRY_PROBABILITY, CHERRY_LIFETIME);
    refreshFieldObjects(lives_, LIFE_PROBABILITY, LIFE_LIFETIME);
    refreshFieldObjects(deaths_, BOMB_PROBABILITY, BOMB_LIFETIME);
}

void Game::print() const
{
    std::cout << currentField() << std::endl;
}

bool Game::isOver() const
{
    return std::all_of(
        playerStates_.begin(),
        playerStates_.end(),
        [] (std::pair<int, PlayerState> p)
        {
            return !p.second.isAlive();
        }
    );
}

bool randomEvent(double prob)
{
    double result = rand() * 1.0 / RAND_MAX;
    return result <= prob;
}

boost::optional<Point> Game::locateFieldObject() const
{
    Field field = currentField();

    int attempts = 0;
    const int MAX_ATTEMPTS = 1000;
    while (attempts < MAX_ATTEMPTS) {
        int x = rand() % width();
        int y = rand() % height();
        if (field.at(x, y) == NOTHING)
            return Point(x, y);
    }
    return boost::none;
}

std::map<int, Snake> Game::snakes(int except) const
{
    std::map<int, Snake> result;
    for (auto playerState: playerStates_) {
        if (playerState.first == except)
            continue;
        if (playerState.second.isAlive()) {
            result[playerState.first] = playerState.second.snake;
        }
    }
    return result;
}

Field Game::currentField(int except) const
{
    return Field(pattern_, snakes(except), cherries_, lives_, deaths_);
}

void Game::refreshFieldObjects(std::vector<FieldObject>& fieldObjects,
                               double appearProbability,
                               int lifetime)
{
    // Remove expired stuff
    std::for_each(
        fieldObjects.begin(),
        fieldObjects.end(),
        [] (FieldObject& obj)
        {
            obj.tick();
        }
    );
    auto last = std::remove_if(
        fieldObjects.begin(),
        fieldObjects.end(),
        [] (const FieldObject& obj)
        {
            return !obj.isAlive();
        }
    );
    fieldObjects.resize(
        std::distance(
            fieldObjects.begin(), last
        )
    );
    // Generate new stuff
    if (randomEvent(appearProbability)) {
        boost::optional<Point> point = locateFieldObject();
        if (point) { // could not find a free cell
            fieldObjects.push_back(FieldObject(lifetime, *point));
        }
    }
}

void Game::removeFieldObject(std::vector<FieldObject>& fieldObjects, const Point& location)
{
    auto result = std::remove_if(fieldObjects.begin(),
                   fieldObjects.end(),
                   [location] (const FieldObject& obj)
                   {
                       return obj.point() == location;
                   }
    );
    fieldObjects.resize(std::distance(fieldObjects.begin(), result));
}
