#include "Game.h"

Game::Game(int size, string title) {
    game_matrix = new RenderWindow(VideoMode(size, size), title); // creating the window
    cell = new Cell(10, 50, 50); // creating the cells
}

void Game::run() {

    // running the window
    while (game_matrix->isOpen()){

        Event close;
        while (game_matrix->pollEvent(close)){
            if (close.type == Event:: Closed){
                game_matrix->close();
            }
        }
        game_matrix->clear();
        cell->draw(game_matrix);
        game_matrix->display();
    }
}
