#include "Constants.h"
#include "Game.h"

int main() {
    Game minesweeper(NUM_OF_COLS, NUM_OF_ROWS);
    minesweeper.main_menu(minesweeper.get_game_window());  // Pass the game window to mainMenu

    return 0;
}