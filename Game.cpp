#include "Constants.h"
#include "Game.h"
#include <sstream>
#include <vector>
#include <string>

Game::Game(int num_cols, int num_rows) {
    
    // creating the window
    game_window = new RenderWindow(VideoMode(CELL_SIZE * num_cols, CELL_SIZE * num_rows), WINDOW_TITLE);
    // sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    // game_window->setPosition(sf::Vector2i((desktop.width - 1000)/8, (desktop.height - 750)/8));
    
    // creating the matrix of cells
    game_matrix = nullptr;

    // intialize game start status
    hasStarted = false;
}

void Game::run() {

    // creating the matrix of cells
    game_matrix = new CellMatrix(NUM_OF_ROWS, NUM_OF_COLS, mine_percentage,game_window); 

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

        //     // hover off settings
        //     if (previousCellIdx != -1) {
        //         Cell* previousCell = game_matrix->get_matrix()[previousCellIdx];
        //         if (previousCell && !previousCell->get_is_reveal()) {
        //             if ((previousCell->get_location()[0] + previousCell->get_location()[1]) % 2 == 0) {
        //                 previousCell->set_color(CELL_COLOR_2); 
        //             } else {
        //                 previousCell->set_color(CELL_COLOR_1); 
        //             }
        //         }
        //     }

        //     // hover for cell
        //     if (cell && !cell->get_is_reveal()) { // check if cell is unrevealed
        //         Color hoverColor = Color(CELL_COLOR_1.r + 40, CELL_COLOR_1.g + 40, CELL_COLOR_1.b + 40);
        //         cell->set_color(hoverColor);
        //     }

        //     // update last cell
        //     previousCellIdx = cell_index;
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

    delete game_matrix;
}

// function to display highscores
void Game::display_stats(RenderWindow* window) {
    // loading font
    Font font;
    if (!font.loadFromFile(ASSETS_PATH+"monospace.ttf")) {
        return;
    }

    // importing csv
    ifstream file(USERDATA_FILE);
    if (!file.is_open()) {
        return;
    }

    string line;
    vector<string> names, scores, accuracies, difficulties;

    // // skip first line
    // getline(file, line);

    // reading csv and pushing to corresponding vectors
    while (getline(file, line)) {
        istringstream ss(line);
        string name, score, accuracy, difficulty;

        getline(ss, name, ',');
        getline(ss, score, ',');
        getline(ss, accuracy, ',');
        getline(ss, difficulty, ',');

        names.push_back(name);
        scores.push_back(score);
        accuracies.push_back(accuracy);
        difficulties.push_back(difficulty);
    }

    file.close();

    // settings headers
    vector<string> headers = { "Username", "Score", "Accuracy", "Difficulty" };

    // 2D vector for data
    vector<vector<string>> data;
    for (int i = 0; i < names.size(); ++i) {
        data.push_back({ names[i], scores[i], accuracies[i], difficulties[i] });
    }

    // get max width of each col
    vector<int> col_widths(headers.size(), 0);
    for (int i = 0; i < headers.size(); ++i) {
        col_widths[i] = headers[i].length();
    }
    for (auto& row : data) {
        for (int i = 0; i < row.size(); ++i) {
            if (row[i].length() > col_widths[i]) {
                col_widths[i] = row[i].length();
            }
        }
    }

    // adding padding
    for (int i = 0; i < col_widths.size(); ++i) {
        col_widths[i] += 2;
    }

    // total table width used for centering
    int total_table_width = 0;
    for (int width : col_widths) {
        total_table_width += width;
    }
    total_table_width += (headers.size() - 1) * 10; 

    // calculating offset to centre align table
    int x_offset = 100; //(windowWidth - total_table_width) / 2 - total_table_width;

    vector<Text> texts;

    // function to create borders
    auto create_border = [&](wstring left, wstring mid, wstring right) {
        wstring border = left;
        for (int i = 0; i < col_widths.size(); ++i) {
            border += wstring(col_widths[i], L'─');
            if (i != col_widths.size() - 1) {
                border += mid;
            }
        }
        border += right;
        return border;
    };

    // top border
    wstring top_border = create_border(L"┌", L"┬", L"┐");
    Text top_borderText(top_border, font);
    top_borderText.setCharacterSize(20);
    top_borderText.setFillColor(Color::White);
    top_borderText.setPosition(x_offset, 100);
    texts.push_back(top_borderText);

    // function to centre text
    auto center_text = [&](string text, int width) {
        int padding = width - text.length();
        int left_padding = padding / 2;
        int right_padding = padding - left_padding;
        return wstring(left_padding, L' ') + wstring(text.begin(), text.end()) + wstring(right_padding, L' ');
    };

    wstring header_row = L"│";
    for (int i = 0; i < headers.size(); ++i) {
        header_row += center_text(headers[i], col_widths[i]) + L"│";
    }
    Text header_text(header_row, font);
    header_text.setCharacterSize(20);
    header_text.setFillColor(Color::White);
    header_text.setPosition(x_offset, 130);
    texts.push_back(header_text);

    wstring mid_border = create_border(L"├", L"┼", L"┤");
    Text mid_border_text(mid_border, font);
    mid_border_text.setCharacterSize(20);
    mid_border_text.setFillColor(Color::White);
    mid_border_text.setPosition(x_offset, 160);
    texts.push_back(mid_border_text);

    // data rows
    for (int i = 0; i < data.size(); ++i) {
        wstring row = L"│";
        for (int j = 0; j < data[i].size(); ++j) {
            row += center_text(data[i][j], col_widths[j]) + L"│";
        }
        Text data_text(row, font);
        data_text.setCharacterSize(20);
        data_text.setFillColor(Color::White);
        data_text.setPosition(x_offset, 190 + i * 30);
        texts.push_back(data_text);
    }

    // bottom border
    wstring bottom_border = create_border(L"└", L"┴", L"┘");
    Text bottom_border_text(bottom_border, font);
    bottom_border_text.setCharacterSize(20);
    bottom_border_text.setFillColor(Color::White);
    bottom_border_text.setPosition(x_offset, 190 + data.size() * 30);
    texts.push_back(bottom_border_text);

    // render table
    while (window->isOpen()) {
        Event event;
        window->clear();

        for (int i = 0; i < texts.size(); ++i) {
            window->draw(texts[i]);
        }

        while (window->pollEvent(event)) {
            if (event.type == Event::Closed) {
                window->close();
            }
        }
        window->display();
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

    // Difficulty buttons (for difficulty selection screen)
    RectangleShape easyButton(Vector2f(250, 75));
    easyButton.setFillColor(BUTTON_COLOR);
    easyButton.setPosition(600, 300);
    easyButton.setOutlineThickness(2);
    easyButton.setOutlineColor(Color::White);

    RectangleShape mediumButton(Vector2f(250, 75));
    mediumButton.setFillColor(BUTTON_COLOR);
    mediumButton.setPosition(600, 400);
    mediumButton.setOutlineThickness(2);
    mediumButton.setOutlineColor(Color::White);

    RectangleShape hardButton(Vector2f(250, 75));
    hardButton.setFillColor(BUTTON_COLOR);
    hardButton.setPosition(600, 500);
    hardButton.setOutlineThickness(2);
    hardButton.setOutlineColor(Color::White);

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
    Text playText, helpText, statsText, nextText, easyText, mediumText, hardText;;
    playText.setFont(font);
    playText.setString("Play");
    playText.setCharacterSize(30);
    playText.setFillColor(Color::Black);
    playText.setPosition(playButton.getPosition().x + 30, playButton.getPosition().y + 25);

    easyText.setFont(font);
    easyText.setString("Easy");
    easyText.setCharacterSize(30);
    easyText.setFillColor(Color::Black);
    easyText.setPosition(easyButton.getPosition().x + 60, easyButton.getPosition().y + 25);

    mediumText.setFont(font);
    mediumText.setString("Medium");
    mediumText.setCharacterSize(30);
    mediumText.setFillColor(Color::Black);
    mediumText.setPosition(mediumButton.getPosition().x + 40, mediumButton.getPosition().y + 25);

    hardText.setFont(font);
    hardText.setString("Hard");
    hardText.setCharacterSize(30);
    hardText.setFillColor(Color::Black);
    hardText.setPosition(hardButton.getPosition().x + 60, hardButton.getPosition().y + 25);

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
    bool selectingDifficulty = false;
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
                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        selectingDifficulty = true;
                        // isPlaying = true;   // Start the game
                        inMenu = false;
                    } else if (helpButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        inHelp = true; // Show help page
                        inMenu = false;
                    } else if (statsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        display_stats(window);
                    }
                }
            }

            // changing help instruction images
            if (inHelp && event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
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

        // Difficulty selection screen
        if (selectingDifficulty) {
            Vector2i mousePos = Mouse::getPosition(*window);

            // Easy Button hover effect
            if (easyButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                easyButton.setFillColor(Color(BUTTON_COLOR));
                easyButton.setOutlineColor(Color::Black);
            } else {
                easyButton.setFillColor(Color(BUTTON_COLOR.r - 30, BUTTON_COLOR.g - 10, BUTTON_COLOR.b - 10)); // Decrease brightness
                easyButton.setOutlineColor(Color::White);
            }

            // Medium Button hover effect
            if (mediumButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                mediumButton.setFillColor(Color(BUTTON_COLOR));
                mediumButton.setOutlineColor(Color::Black);
            } else {
                mediumButton.setFillColor(Color(BUTTON_COLOR.r - 30, BUTTON_COLOR.g - 10, BUTTON_COLOR.b - 10)); // Decrease brightness
                mediumButton.setOutlineColor(Color::White);
            }

            // Hard Button hover effect
            if (hardButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                hardButton.setFillColor(Color(BUTTON_COLOR));
                hardButton.setOutlineColor(Color::Black);
            } else {
                hardButton.setFillColor(Color(BUTTON_COLOR.r - 30, BUTTON_COLOR.g - 10, BUTTON_COLOR.b - 10)); // Decrease brightness
                hardButton.setOutlineColor(Color::White);
            }
            
            // Handle mouse clicks to select difficulty
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                if (easyButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    mine_percentage = 0.1; // Easy difficulty
                    isPlaying = true; // Start game after difficulty is chosen
                    selectingDifficulty = false;
                }
                if (mediumButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    mine_percentage = 0.5; // Medium difficulty
                    isPlaying = true; // Start game
                    selectingDifficulty = false;
                }
                if (hardButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    mine_percentage = 0.7; // Hard difficulty
                    isPlaying = true; // Start game
                    selectingDifficulty = false;
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
        } else if (selectingDifficulty) {
            window->draw(easyButton);
            window->draw(easyText);
            window->draw(mediumButton);
            window->draw(mediumText);
            window->draw(hardButton);
            window->draw(hardText);
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
    highscores_file << username << "," << score << "," << time_taken << "," << difficulty << endl;
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
        if (clock.getElapsedTime().asMilliseconds() >= ( ANIMATION_DURATION / (game_matrix->get_num_cols()*game_matrix->get_num_rows()*mine_percentage))) {
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
    // delete game_matrix;
}
 