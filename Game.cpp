#include "Game.h"

Game::Game(int size, string title) {
    game_window = new RenderWindow(VideoMode(size, size), title); // creating the window
    cell = new Cell(20, 0, 0); // creating the cells
}

void Game::run() {

    // running the window
    while (game_window->isOpen()){

        Event close;
        while (game_window->pollEvent(close)){
            if (close.type == Event:: Closed){
                game_window->close();
            }
        }
        game_window->clear();
        cell->draw(game_window);
        game_window->display();
    }
}
