#include "Constants.h"
#include "Game.h"
#include "Constants.h"

Game::Game(int num_cols, int num_rows) {
    game_window = new RenderWindow(VideoMode(CELL_SIZE * num_cols, CELL_SIZE * num_rows), "MineSweeper"); // creating the window
    game_matrix = new CellMatrix(num_cols, num_rows); // creating the matrix of cells
}

void Game::run() {

    // running the window
    while (game_window->isOpen()){

        Event close; // to close the window
        while (game_window->pollEvent(close)){
            if (close.type == Event:: Closed){
                game_window->close();
            }
        }

        game_window->clear();

        // display the matrix
        game_matrix->display();

        // display the window
        game_window->display();
    }
}
