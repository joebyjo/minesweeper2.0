#include "Constants.h"
#include "Game.h"

Game::Game(int num_cols, int num_rows) {
    
    // creating the window
    game_window = new RenderWindow(VideoMode(CELL_SIZE * num_cols, CELL_SIZE * num_rows), WINDOW_TITLE); 
    
    // creating the matrix of cells
    game_matrix = new CellMatrix(num_rows, num_cols); 
}

void Game::mainMenu(sf::RenderWindow* window) {
    sf::Font font;
    if (!font.loadFromFile("assets/BroncoPersonalUse.ttf")) {
        std::cout << "Error loading font" << std::endl;
        return;  
    }
    
    // loading each frame of gif
    sf::Texture textures[20];
    for (int i = 0; i < 20; ++i) { 
        if (!textures[i].loadFromFile("assets/frame" + std::to_string(i + 1) + ".gif")) { 
            std::cout << "Error loading frame " << (i + 1) << std::endl;
            return;
        }
    }

    // Creating buttons
    sf::RectangleShape playButton(sf::Vector2f(125, 75));
    playButton.setFillColor(sf::Color(70, 130, 180));
    playButton.setPosition(500, 300);
    playButton.setOutlineThickness(2);
    playButton.setOutlineColor(sf::Color::White);

    sf::RectangleShape howToPlayButton(sf::Vector2f(125, 75));
    howToPlayButton.setFillColor(sf::Color(70, 130, 180));
    howToPlayButton.setPosition(625, 425);
    howToPlayButton.setOutlineThickness(2);
    howToPlayButton.setOutlineColor(sf::Color::White);

    sf::RectangleShape statsButton(sf::Vector2f(125, 75));
    statsButton.setFillColor(sf::Color(70, 130, 180));
    statsButton.setPosition(750, 550);
    statsButton.setOutlineThickness(2);
    statsButton.setOutlineColor(sf::Color::White);

    // labels
    sf::Text playGameText, howToPlayText, statsText;
    playGameText.setFont(font);
    playGameText.setString("Play");
    playGameText.setCharacterSize(40);
    playGameText.setFillColor(sf::Color::Black);
    playGameText.setPosition(playButton.getPosition().x + 30, playButton.getPosition().y + 10);

    howToPlayText.setFont(font);
    howToPlayText.setString("Help");
    howToPlayText.setCharacterSize(40);
    howToPlayText.setFillColor(sf::Color::Black);
    howToPlayText.setPosition(howToPlayButton.getPosition().x + 30, howToPlayButton.getPosition().y + 10);

    statsText.setFont(font);
    statsText.setString("Stats");
    statsText.setCharacterSize(40);
    statsText.setFillColor(sf::Color::Black);
    statsText.setPosition(statsButton.getPosition().x + 30, statsButton.getPosition().y + 10);

    // Help text
    sf::Text howToPlayInstructions;
    howToPlayInstructions.setFont(font);
    howToPlayInstructions.setString("How to Play:\n- Left click to reveal a cell.\n- Right click to flag a cell.\nPress Enter to return.");
    howToPlayInstructions.setCharacterSize(24);
    howToPlayInstructions.setFillColor(sf::Color::White);
    howToPlayInstructions.setPosition(100, 150);

    // Status
    bool isPlaying = false;
    bool inMenu = true;
    bool inHowToPlay = false;

    // Frame timing
    float frameDuration = 0.1f; 
    sf::Clock frameClock;
    int currentFrame = 0; // Index for current frame

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            if (inMenu && !isPlaying) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                    if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        isPlaying = true;   // Start the game
                        inMenu = false;     
                    } else if (howToPlayButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        inHowToPlay = true; // Show help page
                        inMenu = false;      
                    } else if (statsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << "Stats button clicked!" << std::endl;
                    }
                }
            }
        }

        // updating current frame
        if (frameClock.getElapsedTime().asSeconds() >= frameDuration) {
            currentFrame = (currentFrame + 1) % 20;
            frameClock.restart();
        }

        window->clear(); // Clear the window

        // draw stuff
        sf::Sprite backgroundSprite;
        backgroundSprite.setTexture(textures[currentFrame]);
        window->draw(backgroundSprite);

        if (inMenu) {
            window->draw(playButton);
            window->draw(playGameText);
            window->draw(howToPlayButton);
            window->draw(howToPlayText);
            window->draw(statsButton);
            window->draw(statsText);
        } else if (inHowToPlay) {
            window->draw(howToPlayInstructions);
        }

        window->display();

        if (isPlaying) {
            run();  // Start game in same window
            inMenu = true;  
            isPlaying = false;
        }
    }
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