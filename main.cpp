#include "Game.h"
#include "Constants.h"

int main()
{

    Game minesweeper(NUM_OF_COLS, NUM_OF_ROWS);
    minesweeper.run();

    return 0;
}