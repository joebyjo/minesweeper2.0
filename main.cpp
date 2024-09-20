#include "Game.h"

int main()
{
    const int size_window = 1000;

    Game minesweeper(size_window, "MINESWEEPER");
    minesweeper.run();

    return 0;
}