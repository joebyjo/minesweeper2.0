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
            } else if (close.type == Event::MouseButtonReleased){
                if (close.mouseButton.button == sf::Mouse::Left) {
                    // cout << static_cast<int>(floor(.x));
                    sf::Vector2i mousePos = sf::Mouse::getPosition(*game_window);
                    int mouseX = mousePos.x;
                    int mouseY = mousePos.y;


                    cout << mouseX << " " << mouseY << endl;


                    }
                else if (close.mouseButton.button == sf::Mouse::Right) {cout << "joe" << endl;}
            }


        }
        game_window->clear();
        cell->draw(game_window);
        game_window->display();

        
    }
}
