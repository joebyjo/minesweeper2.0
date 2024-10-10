#include "Constants.h"
#include "Game.h"

Game::Game(int num_cols, int num_rows) {
    
    // creating the window
    game_window = new RenderWindow(VideoMode(CELL_SIZE * num_cols, CELL_SIZE * num_rows), WINDOW_TITLE); 
    
    // creating the matrix of cells
    game_matrix = new CellMatrix(num_rows, num_cols); 
}

void Game::mainMenu(RenderWindow* window) {

    game_window->create(VideoMode(1000, 750), "Main Menu");
    Font font;  
    if (!font.loadFromFile("assets/8bit.ttf")) {
        return;
    }

    Font font1; 
    if (!font1.loadFromFile("assets/monospace.ttf")) {
        return;
    }

    // gif1 frames
    Texture gif1Textures[20]; 
    for (int i = 0; i < 20; ++i) {
        if (!gif1Textures[i].loadFromFile("assets/gif1/g1f" + to_string(i + 1) + ".png")) {
            return;
        }
    }

    // gif2 frames
    Texture gif2Textures[20];
    for (int i = 0; i < 20; ++i) {
        if (!gif2Textures[i].loadFromFile("assets/gif2/g2f" + to_string(i + 1) + ".png")) {
            return;
        }
    }

    // help images
    Texture helpImages[4];
    for (int i = 0; i < 4; ++i) {
        if (!helpImages[i].loadFromFile("assets/help/h" + to_string(i + 1) + ".png")) {
            return;
        }
    }

    // Creating buttons
    RectangleShape playButton(Vector2f(175, 75));
    playButton.setFillColor(BUTTON_COLOR);
    playButton.setPosition(500, 300);
    playButton.setOutlineThickness(2);
    playButton.setOutlineColor(Color::White);

    RectangleShape helpButton(Vector2f(175, 75));
    helpButton.setFillColor(Color(BUTTON_COLOR));
    helpButton.setPosition(625, 425);
    helpButton.setOutlineThickness(2);
    helpButton.setOutlineColor(Color::White);

    RectangleShape statsButton(Vector2f(200, 75));
    statsButton.setFillColor(BUTTON_COLOR);
    statsButton.setPosition(750, 550);
    statsButton.setOutlineThickness(2);
    statsButton.setOutlineColor(Color::White);

    RectangleShape nextButton(Vector2f(75, 50));
    nextButton.setFillColor(BUTTON_COLOR);
    nextButton.setPosition(850, 650);
    nextButton.setOutlineThickness(2);
    nextButton.setOutlineColor(Color::White);

    // Labels
    Text playText, helpText, statsText, nextText;
    playText.setFont(font);
    playText.setString("Play");
    playText.setCharacterSize(30);
    playText.setFillColor(Color::Black);
    playText.setPosition(playButton.getPosition().x + 30, playButton.getPosition().y + 25);

    helpText.setFont(font);
    helpText.setString("Help");
    helpText.setCharacterSize(30);
    helpText.setFillColor(Color::Black);
    helpText.setPosition(helpButton.getPosition().x + 30, helpButton.getPosition().y + 25);

    statsText.setFont(font);
    statsText.setString("Stats");
    statsText.setCharacterSize(30);
    statsText.setFillColor(Color::Black);
    statsText.setPosition(statsButton.getPosition().x + 30, statsButton.getPosition().y + 25);

    nextText.setFont(font1);
    nextText.setString("Next");
    nextText.setCharacterSize(18);
    nextText.setFillColor(Color::Black);
    nextText.setPosition(nextButton.getPosition().x + 15, nextButton.getPosition().y + 15);

    // Status
    bool isPlaying = false;
    bool inMenu = true;
    bool inHelp = false;
    int currentImageIndex = 0;

    // Frame timing
    float frameDuration = 0.1f; 
    Clock frameClock;
    int currentFrame = 0; // Index for current frame
    bool firstGifFinished = false;

    while (window->isOpen()) {
        Event event;
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed) {
                window->close();
            }

            if (inMenu && !isPlaying) {
                Vector2i mousePos = Mouse::getPosition(*window);

                // hover effect
                if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    playButton.setFillColor(Color(BUTTON_COLOR));  
                    playButton.setOutlineColor(Color::Black);      
                } else {
                    playButton.setFillColor(Color(BUTTON_COLOR.r - 30, BUTTON_COLOR.g - 10, BUTTON_COLOR.b - 10));   
                    playButton.setOutlineColor(Color::White);      
                }

                if (helpButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    helpButton.setFillColor(Color(BUTTON_COLOR));
                    helpButton.setOutlineColor(Color::Black);
                } else {
                    helpButton.setFillColor(Color(BUTTON_COLOR.r - 30, BUTTON_COLOR.g - 10, BUTTON_COLOR.b - 10));   
                    helpButton.setOutlineColor(Color::White);
                }

                if (statsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    statsButton.setFillColor(Color(BUTTON_COLOR));
                    statsButton.setOutlineColor(Color::Black);
                } else {
                    statsButton.setFillColor(Color(BUTTON_COLOR.r - 30, BUTTON_COLOR.g - 10, BUTTON_COLOR.b - 10));   
                    statsButton.setOutlineColor(Color::White);
                }

                // button controls
                if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                    if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        isPlaying = true;   // Start the game
                        inMenu = false;
                    } else if (helpButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        inHelp = true; // Show help page
                        inMenu = false;
                    } else if (statsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    }
                }
            }

            if (inHelp && event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                Vector2i mousePos = Mouse::getPosition(*window);
                if (nextButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    currentImageIndex++; 
                    if (currentImageIndex == 4) { 
                        currentImageIndex = 0; 
                        inHelp = false; 
                        inMenu = true; 
                    }
                }
            }
        }

        // update current frame
        if (frameClock.getElapsedTime().asSeconds() >= frameDuration) {
            if (!firstGifFinished) {
                currentFrame++;
                if (currentFrame >= 20) {
                    currentFrame = 0;  // reset for 2nd gif
                    firstGifFinished = true;  // 1st gif done
                }
            } else {
                currentFrame = (currentFrame + 1) % 20; // loop for 2nd gif
            }
            frameClock.restart(); // keep playing 2nd gif
        }

        window->clear(MAIN_BG_COLOR); 

        // Draw gif frames
        Sprite backgroundSprite;
        if (!firstGifFinished) {
            backgroundSprite.setTexture(gif1Textures[currentFrame]); // Draw 1st gif
        } else {
            backgroundSprite.setTexture(gif2Textures[currentFrame]); // Draw 2nd gif
        }
        window->draw(backgroundSprite);

        // Draw other stuff
        if (inMenu) {
            window->draw(playButton);
            window->draw(playText);
            window->draw(helpButton);
            window->draw(helpText);
            window->draw(statsButton);
            window->draw(statsText);
        } else if (inHelp) {
            Sprite helpSprite;
            helpSprite.setTexture(helpImages[currentImageIndex]); 
            window->draw(helpSprite);

            window->draw(nextButton);
            window->draw(nextText);
        }

        window->display(); 

        if (isPlaying) {
            run(); 
            inMenu = true;
            isPlaying = false;
        }
    }
}

void Game::run() {
    game_window->create(VideoMode(CELL_SIZE * game_matrix->get_num_cols(),
                                 CELL_SIZE * game_matrix->get_num_rows()), WINDOW_TITLE);
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
                if (event.mouseButton.button == Mouse::Left) {
                    
                    Vector2i mousePos = Mouse::getPosition(*game_window);

                    // ensure resizing window doesnt change coords
                    Vector2f worldPos = game_window->mapPixelToCoords(mousePos);
                    
                    int mouseX = worldPos.x;
                    int mouseY = worldPos.y;

                    int cell_index_x = mouseX / CELL_SIZE;
                    int cell_index_y = mouseY / CELL_SIZE;

                    // y * num_cols + x
                    game_matrix->get_matrix()[cell_index_y* game_matrix->get_num_cols() + cell_index_x]->reveal(game_matrix);


                    }
                else if (event.mouseButton.button == Mouse::Right) {

                    Vector2i mousePos = Mouse::getPosition(*game_window);

                    // ensure resizing window doesnt change coords
                    Vector2f worldPos = game_window->mapPixelToCoords(mousePos);
                    
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