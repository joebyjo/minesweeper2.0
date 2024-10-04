#include "Game.h"
#include "Constants.h"

int main()
{

    Game minesweeper(NUM_OF_COLS, NUM_OF_ROWS);
    minesweeper.run();

    // Game minesweeper3(5, 7);
    // minesweeper3.run();

    // Game minesweeper4(10, 25);
    // minesweeper4.run();

    return 0;
}