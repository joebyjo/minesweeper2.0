#include "Constants.h"
#include "Game.h"

Game::Game(int num_cols, int num_rows) {
    
    // creating the window
    game_window = new RenderWindow(VideoMode(CELL_SIZE * num_cols, CELL_SIZE * num_rows), WINDOW_TITLE); 
    
    // creating the matrix of cells
    game_matrix = new CellMatrix(num_rows, num_cols); 
}

void Game::run() {

    // running the window
    while (game_window->isOpen()){

        Event close; // to close the window
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

        // display the matrix
        game_matrix->display(game_window);

        // display the window
        game_window->display();

        
    }
}
