#include "game.h"
#include "dumb_player.h"

#include "unistd.h"


const int HEIGHT = 20;
const int WIDTH = 20;

const int INTERVAL = 0;
const int MAX_TURNS = 5000;

const int START_X_0 = 5;
const int START_Y_0 = 5;
const int START_X_1 = 5;
const int START_Y_1 = 15;
const int START_X_2 = 15;
const int START_Y_2 = 15;
const int START_X_3 = 15;
const int START_Y_3 = 5;

const int START_LIVES = 1;


int main()
{
    // Generate empty field without walls
    std::vector<std::vector<FieldType>> pattern;
    for (int i = 0; i < HEIGHT; ++i) {
        pattern.push_back(std::vector<FieldType>());
        for (int j = 0; j < WIDTH; ++j) {
            pattern[i].push_back(NOTHING);
        }
    }

    // Create players
    Player * first = new DumbPlayer(0, UP);
    Player * second = new DumbPlayer(1, RIGHT);
    Player * third = new DumbPlayer(2, LEFT);
    Player * fourth = new DumbPlayer(3, DOWN);

    // Create start player states
    std::vector<PlayerState> startStates {
        PlayerState(
            first,
            Snake(
                Point(START_X_0, START_Y_0),
                { RIGHT, RIGHT, RIGHT }
            ),
            START_LIVES
        ),
        PlayerState(
            second,
            Snake(
                Point(START_X_1, START_Y_1),
                { RIGHT, RIGHT, RIGHT }
            ),
            START_LIVES
        ),
        PlayerState(
            third,
            Snake(
                Point(START_X_2, START_Y_2),
                { LEFT, LEFT, LEFT }
            ),
            START_LIVES
        ),
        PlayerState(
            fourth,
            Snake(
                Point(START_X_3, START_Y_3),
                { LEFT, LEFT, LEFT }
            ),
            START_LIVES
        )
    };

    // Go snake, I've created
    Game game(pattern, startStates, MAX_TURNS);

    std::cout << "Beginning:" << std::endl;
    game.print();
    sleep(INTERVAL);

    int counter = 0;
    while (!game.isOver()) {
        game.move();
        std::cout << "Turn " << ++counter << std::endl;
        game.print();
        sleep(INTERVAL);
    }

    delete first;
    delete second;
    delete third;
    delete fourth;

    return 0;
}
