#include "Game.h"
#include "Constants.h"

int main()
{
    const int num_rows = 20;
    const int num_cols = 20;

    Game minesweeper(num_cols, num_rows);
    minesweeper.run();

    return 0;
}