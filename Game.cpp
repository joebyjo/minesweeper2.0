#include "Constants.h"
#include "Game.h"

Game::Game(int num_cols, int num_rows) {
    
    // creating the window
    game_window = new RenderWindow(VideoMode(CELL_SIZE * num_cols, CELL_SIZE * num_rows), WINDOW_TITLE);
    // sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    // game_window->setPosition(sf::Vector2i((desktop.width - 1000)/8, (desktop.height - 750)/8));
    
    // creating the matrix of cells
    game_matrix = new CellMatrix(num_rows, num_cols, game_window); 

    // intialize game start status
    hasStarted = false;
}

void Game::run() {
    // game window (dynamic size)
    game_window->create(VideoMode(CELL_SIZE * game_matrix->get_num_cols(),
                                  CELL_SIZE * game_matrix->get_num_rows() + 50), WINDOW_TITLE);

    // shape for progress bar (hollow)
    RectangleShape progressBarBg(Vector2f(game_window->getSize().x / 4, 20)); 
    progressBarBg.setFillColor(Color(150, 150, 150));    
    progressBarBg.setPosition((game_window->getSize().x) * 3 / 5, CELL_SIZE * game_matrix->get_num_rows() + 15); 

    // shape for progress bar (filled)
    RectangleShape progressBar(Vector2f(0, 20));             
    progressBar.setFillColor(Color(50, 200, 50));                 
    progressBar.setPosition((game_window->getSize().x) * 3 / 5, CELL_SIZE * game_matrix->get_num_rows() + 15);  

    // shape for space behind progress bar
    RectangleShape extraBg(Vector2f(game_window->getSize().x, 50)); 
    extraBg.setFillColor(Color(153, 0, 0)); 
    extraBg.setPosition(0, CELL_SIZE * game_matrix->get_num_rows());

    game_matrix->set_gameboard();
    set_is_first_click(true);

    int current_mine_index = 0;
    // reveal all cells for testing purposes
    // game_matrix->reveal_all_cells();
    int totalCells = game_matrix->get_num_rows() * game_matrix->get_num_cols();

    // variable to store time when game ends
    int final_time = 0.0;
    bool timer_stopped = false;  // time stopper
    bool timer_started = false;  // time starter

    // load font for timer
    Font timerfont; 
    if (!timerfont.loadFromFile("assets/monospace.ttf")) {
        return;
    }

    // int previousCellIdx = -1;
    while (game_window->isOpen()) {
        Event event;
        while (game_window->pollEvent(event)) {

            Vector2i mousePos = Mouse::getPosition(*game_window);
            Vector2f worldPos = game_window->mapPixelToCoords(mousePos);
            int cell_index_x = worldPos.x / CELL_SIZE;
            int cell_index_y = worldPos.y / CELL_SIZE; 
            int cell_index = cell_index_y * game_matrix->get_num_cols() + cell_index_x;
            // Cell* cell = nullptr;

            // if (cell_index >= 0 && cell_index < totalCells) {
            //     cell = game_matrix->get_matrix()[cell_index];
            // }
            if (event.type == Event::Closed) {
                game_window->close();
            } else if (event.type == Event::MouseButtonReleased && !game_matrix->get_gameover()) {

                // ensuring clicking progress bar doesn't cause errors
                if (totalCells > cell_index) {
                    if (event.mouseButton.button == Mouse::Left) {
                        // start the timer on first click
                        if (!timer_started) {
                            game_timer.restart();  // reset timer
                            timer_started = true;   // update timer state
                        }

                        if (is_first_click){
                            check_first_click(cell_index_x, cell_index_y);
                        }
                        
                        game_matrix->get_matrix()[cell_index]->reveal(game_matrix);
                    } else if (event.mouseButton.button == Mouse::Right) {
			            if (!timer_started) {
                            game_timer.restart();  // reset timer
                            timer_started = true;   // update timer state
                        }
                        game_matrix->get_matrix()[cell_index]->flag(game_window);
                    }
                }
            } else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                game_window->close();
            }
        }

        // progress bar formula
        int revealedCells = game_matrix->get_revealed_cells();  
        float revealPercentage = (float)revealedCells / (totalCells - game_matrix->get_num_mines());
        progressBar.setSize(Vector2f(game_window->getSize().x / 4 * revealPercentage, 20));  

        // draw on window
        game_window->clear();

        // Timer settings
        int elapsed = (int)(game_timer.getElapsedTime().asSeconds());
        string timerText;

        if (!timer_started) {
            timerText = "Time: 0s"; // display 0 if not started
        } else if (!game_matrix->get_gameover() && !check_game_win()) {
            final_time = elapsed;  // update time till game running
            timerText = "Time: " + to_string(final_time) + "s";
        } else if (game_matrix->get_gameover() || check_game_win()) {
            timer_stopped = true; // stop timer once game over
        }

        if (timer_stopped) {
            timerText = "Time: " + to_string(final_time) + "s"; // display final time
        }

        // displaying timer
        Text timerDisplay(timerText, timerfont);
        timerDisplay.setCharacterSize(20);
        timerDisplay.setFillColor(Color::White);
        timerDisplay.setPosition((game_window->getSize().x * 3 / 25), CELL_SIZE * game_matrix->get_num_rows() + 12.5);
        

        // if game end, reveal mines with animation
        if (game_matrix->get_gameover()){
            if (play_animation()) { 
                // TODO
            }

        } if (check_game_win()){
            if (play_animation()) {
                int score = (game_matrix->get_num_mines() * 1000)/ final_time;
                append_highscore("joe",score,final_time,"easy");
            }
        }

        game_window->draw(extraBg);
        game_window->draw(timerDisplay);
        game_window->draw(progressBarBg);
        game_window->draw(progressBar);
        game_matrix->display(game_window);
        game_window->display();
    }
}

void Game::mainMenu(RenderWindow* window) {
    // main menu window (fixed size)
    game_window->create(VideoMode(1000, 750), "Main Menu");

    // loading fonts
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

    // while user on main menu window
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
                    playButton.setFillColor(Color(BUTTON_COLOR.r - 30, BUTTON_COLOR.g - 10, BUTTON_COLOR.b - 10));   // decrease brightness
                    playButton.setOutlineColor(Color::White);      
                }

                if (helpButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    helpButton.setFillColor(Color(BUTTON_COLOR));
                    helpButton.setOutlineColor(Color::Black);
                } else {
                    helpButton.setFillColor(Color(BUTTON_COLOR.r - 30, BUTTON_COLOR.g - 10, BUTTON_COLOR.b - 10));   // decrease brightness
                    helpButton.setOutlineColor(Color::White);
                }

                if (statsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    statsButton.setFillColor(Color(BUTTON_COLOR));
                    statsButton.setOutlineColor(Color::Black);
                } else {
                    statsButton.setFillColor(Color(BUTTON_COLOR.r - 30, BUTTON_COLOR.g - 10, BUTTON_COLOR.b - 10));   // decrease brightness
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

            // changing help instruction images
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

        // Draw everything else
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

void Game::append_highscore(string username,int score,int time_taken,string difficulty) {
    // open file and append game stats to csv file
    ofstream highscores_file;
    highscores_file.open(USERDATA_FILE, ios::app);
    highscores_file << username << "," << score << "," << time_taken << "," << difficulty << std::endl;
    highscores_file.close();
}

void Game::check_first_click(int cell_index_x, int cell_index_y) {
    set_is_first_click(false); // setting the first clisck as false

    game_matrix->first_click(cell_index_x, cell_index_y);

}
        

bool Game::play_animation() {
    static Clock clock;
    static int current_mine_index = 0;
    static bool animation_done = false;

    if (animation_done) {
        return false; // if done, then dont continue
    }

    if (current_mine_index < game_matrix->get_mine_locations().size()) {
        if (clock.getElapsedTime().asMilliseconds() >= ANIMATION_DELAY) {
            int location = game_matrix->get_mine_locations()[current_mine_index];
            Cell* mine = game_matrix->get_matrix()[location];

            if (game_matrix->get_gameover()) {
                if (!mine->get_is_reveal()) {
                    if (mine->get_is_flagged()) {
                        mine->flag(game_window);
                    }
                    mine->reveal(game_matrix);
                }
            } else if (check_game_win()) {
                if (!mine->get_is_reveal()) {
                    mine->set_color(Color::White);
                }
            }

            current_mine_index++;
            clock.restart();
        }
    }

    // check if all mines revealed
    if (current_mine_index >= game_matrix->get_mine_locations().size()) {
        animation_done = true;
        return true;
    }

    return false;
}


bool Game::check_game_win() {

    if (game_matrix->get_revealed_cells()== ((game_matrix->get_num_cols()*game_matrix->get_num_rows())-game_matrix->get_num_mines())) {
        return true;
    }

    return false;
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

bool Game::get_is_first_click() { return is_first_click; }

// set game window manually
void Game:: set_game_window(RenderWindow* game_window) {
    this->game_window = game_window;
};

// set game matrix manually
void Game:: set_game_matrix(CellMatrix* game_matrix) {
    this->game_matrix = game_matrix;
}
void Game::set_is_first_click(bool is_first_click) { this->is_first_click = is_first_click; };

// destroy all attached objects 
Game:: ~Game() {
    delete game_window;
    delete game_matrix;
}
 