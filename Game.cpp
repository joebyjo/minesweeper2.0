#include "Game.h"

Game::Game(int size, string title) {
    game_matrix = new RenderWindow(VideoMode(size, size), title);
}

void Game::run() {
    while (game_matrix->isOpen()){

        Event close;
        while (game_matrix->pollEvent(close)){
            if (close.type == Event:: Closed){
                game_matrix->close();
            }
        }
        game_matrix->clear();
        game_matrix->display();
    }
}
