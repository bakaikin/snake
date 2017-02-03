#include "game.h"
#include "dumb_player.h"

#include "unistd.h"


const int HEIGHT = 20;
const int WIDTH = 30;

const int INTERVAL = 2;
const int MAX_TURNS = 50;


int main()
{
    // Generate empty field without walls
    vector<vector<FieldType>> pattern;
    for (int i = 0; i < HEIGHT; ++i) {
        pattern.push_back(vector<FieldType>());
        for (int j = 0; j < WIDTH; ++j) {
            pattern[i].push_back(NOTHING);
        }
    }

    // Create players
    Player * first = new DumbPlayer(0, UP);
    Player * second = new DumbPlayer(1, RIGHT);
    Player * third = new DumbPlayer(2, LEFT);
    Player * fourth = new DumbPlayer(3, DOWN);

    // Go snake, I've created
    Game game(pattern, first, second, third, fourth);

    std::cout << "Beginning:" << std::endl;
    game.print();
    sleep(INTERVAL);

    int counter = 0;
    while (!game.isOver() && ++counter < MAX_TURNS) {
        game.move();
        std::cout << "Turn " << counter << std::endl;
        game.print();
        sleep(INTERVAL);
    }

    return 0;
}
