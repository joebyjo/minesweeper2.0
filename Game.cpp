#include "Constants.h"
#include "Game.h"

Game::Game(int num_cols, int num_rows) {
    
    // creating the window
    game_window = new RenderWindow(VideoMode(CELL_SIZE * num_cols, CELL_SIZE * num_rows), WINDOW_TITLE); 
    
    // creating the matrix of cells
    game_matrix = new CellMatrix(num_rows, num_cols, game_window); 
}

void Game::run() {

    // setting mines randomly
    game_matrix->set_gameboard();

    Clock reveal_clock;
    int current_mine_index = 0;

    // reveal all cells for testing purposes
    // game_matrix->reveal_all_cells();

    // running the window
    while (game_window->isOpen()){

        Event event; // to close the window
        while (game_window->pollEvent(event)){
            if (event.type == Event:: Closed){
                game_window->close();
            } else if (event.type == Event::MouseButtonReleased && !(game_matrix->get_gameover())){  // don't take input after gameover
                if (event.mouseButton.button == sf::Mouse::Left) {
                    
                    sf::Vector2i mousePos = sf::Mouse::getPosition(*game_window);

                    // ensure resizing window doesnt change coords
                    sf::Vector2f worldPos = game_window->mapPixelToCoords(mousePos);
                    
                    int mouseX = worldPos.x;
                    int mouseY = worldPos.y;

                    int cell_index_x = mouseX / CELL_SIZE;
                    int cell_index_y = mouseY / CELL_SIZE;

                    // y * num_cols + x
                    game_matrix->get_matrix()[cell_index_y* game_matrix->get_num_cols() + cell_index_x]->reveal(game_matrix);


                    }
                else if (event.mouseButton.button == sf::Mouse::Right) {

                    sf::Vector2i mousePos = sf::Mouse::getPosition(*game_window);

                    // ensure resizing window doesnt change coords
                    sf::Vector2f worldPos = game_window->mapPixelToCoords(mousePos);
                    
                    int mouseX = worldPos.x;
                    int mouseY = worldPos.y;

                    int cell_index_x = mouseX / CELL_SIZE;
                    int cell_index_y = mouseY / CELL_SIZE;

                    // y * num_cols + x
                    game_matrix->get_matrix()[cell_index_y* NUM_OF_COLS + cell_index_x]->flag(game_window);
                    
                }
            } else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    game_window->close();
                }
            }


        }

        game_window->clear();

        // if game is over, reveal mines with animation, if game won, show mine locations with animation
        if ((game_matrix->get_gameover() || game_matrix->check_game_win()) && 
            (current_mine_index < game_matrix->get_mine_locations().size())) {
            
            if (reveal_clock.getElapsedTime().asMilliseconds() >= ANIMATION_DELAY) {
                int location = game_matrix->get_mine_locations()[current_mine_index];
                Cell* mine = game_matrix->get_matrix()[location];

                // animate depending on win or lose
                if (game_matrix->get_gameover()) {
                    // unflag and reveal mine
                    if (!mine->get_is_reveal()) {
                        if (mine->get_is_flagged()) {
                            mine->flag(game_window);
                        }
                        mine->reveal(game_matrix);
                    }
                } else if (game_matrix->check_game_win()) {
                    if (!mine->get_is_reveal()) {
                        mine->set_color(Color::White);
                    }
                }

                current_mine_index++;
                reveal_clock.restart();
            }
        }

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