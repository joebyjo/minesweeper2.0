#include "Constants.h"
#include "Game.h"

Game::Game(int num_cols, int num_rows) {
    
    // creating the window
    game_window = new RenderWindow(VideoMode(CELL_SIZE * num_cols, CELL_SIZE * num_rows), WINDOW_TITLE); 
    
    // creating the matrix of cells
    game_matrix = new CellMatrix(num_rows, num_cols); 
}

void Game::run() {

    // setting mines randomly
    game_matrix->set_gameboard();

    // reveal all cells for testing purposes
    // game_matrix->reveal_all_cells();

    // running the window
    while (game_window->isOpen()){

        Event event; // to close the window
        while (game_window->pollEvent(event)){
            if (event.type == Event:: Closed){
                game_window->close();
            } else if (event.type == Event::MouseButtonReleased){
                if (event.mouseButton.button == sf::Mouse::Left) {
                    
                    sf::Vector2i mousePos = sf::Mouse::getPosition(*game_window);
                    int mouseX = mousePos.x;
                    int mouseY = mousePos.y;

                    int cell_index_x = mouseX / CELL_SIZE;
                    int cell_index_y = mouseY / CELL_SIZE;

                    // y * num_cols + x
                    game_matrix->get_matrix()[cell_index_y* game_matrix->get_num_cols() + cell_index_x]->reveal(game_matrix);


                    }
                else if (event.mouseButton.button == sf::Mouse::Right) {

                    sf::Vector2i mousePos = sf::Mouse::getPosition(*game_window);
                    int mouseX = mousePos.x;
                    int mouseY = mousePos.y;

                    int cell_index_x = mouseX / CELL_SIZE;
                    int cell_index_y = mouseY / CELL_SIZE;

                    // y * num_cols + x
                    // game_matrix->get_matrix()[cell_index_y* NUM_OF_COLS + cell_index_x]->flag();
                    
                }
            }


        }

        game_window->clear();

        // display the matrix
        game_matrix->display(game_window);

        // display the window
        game_window->display();

        
    }
}


// getters and setters
// get game window
RenderWindow* Game:: get_game_window() {
    return this->game_window;
}

// get game matrix
CellMatrix* Game:: get_game_matrix() {
    return this->game_matrix;
}

// set game window manually
void Game:: set_game_window(RenderWindow* game_window) {
    this->game_window = game_window;
};

// set game matrix manually
void Game:: set_game_matrix(CellMatrix* game_matrix) {
    this->game_matrix = game_matrix;
};


// destroy all attached objects 
Game:: ~Game() {
    delete game_window;
    delete game_matrix;
}