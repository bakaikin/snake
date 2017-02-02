#include "game.h"
#include "dumb_player.h"


const int HEIGHT = 20;
const int WIDTH = 20;


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
    Player * first = new DumbPlayer(0, 3);
    Player * second = new DumbPlayer(1, 3);
    Player * third = new DumbPlayer(2, 1);
    Player * fourth = new DumbPlayer(3, 1);

    // Go snake, I've created
    Game game(pattern, first, second, third, fourth);

    std::cout << "Beginning:" << std::endl;
    game.print();

    int counter = 0;
    while (!game.isOver() && ++counter < 3) {
        game.move();
        std::cout << "Turn " << counter << std::endl;
        game.print();
    }

    return 0;
}
