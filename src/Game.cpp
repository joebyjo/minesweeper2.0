#include "Game.h"
#include "Constants.h"
#include <sstream>
#include <string>
#include <vector>

Game::Game(int num_cols, int num_rows) {

    // creating the window
    game_window = new RenderWindow(VideoMode(CELL_SIZE * num_cols, CELL_SIZE * num_rows), WINDOW_TITLE,
                                   Style::Titlebar | Style::Close);
    // sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    // game_window->setPosition(sf::Vector2i((desktop.width - 1000)/8, (desktop.height - 750)/8));

    // creating the matrix of cells
    game_matrix = nullptr;

    // intialize game start status
    hasStarted = false;
}

void Game::run() {

    // creating the matrix of cells
    game_matrix = new CellMatrix(NUM_OF_ROWS, NUM_OF_COLS, mine_percentage, game_window);

    // game window (dynamic size)
    game_window->create(
        VideoMode(CELL_SIZE * game_matrix->get_num_cols(), CELL_SIZE * game_matrix->get_num_rows() + 50), WINDOW_TITLE,
        Style::Titlebar | Style::Close);

    // shape for progress bar (hollow)
    RectangleShape progress_bar_bg(Vector2f(game_window->getSize().x / 4, 20));
    progress_bar_bg.setFillColor(Color(150, 150, 150));
    progress_bar_bg.setPosition((game_window->getSize().x) * 3 / 5, CELL_SIZE * game_matrix->get_num_rows() + 15);

    // shape for progress bar (filled)
    RectangleShape progress_bar(Vector2f(0, 20));
    progress_bar.setFillColor(Color(50, 200, 50));
    progress_bar.setPosition((game_window->getSize().x) * 3 / 5, CELL_SIZE * game_matrix->get_num_rows() + 15);

    // shape for space behind progress bar
    RectangleShape extra_bg(Vector2f(game_window->getSize().x, 50));
    extra_bg.setFillColor(Color(153, 0, 0));
    extra_bg.setPosition(0, CELL_SIZE * game_matrix->get_num_rows());

    game_matrix->set_gameboard();
    set_is_first_click(true);

    // reveal all cells for testing purposes
    // game_matrix->reveal_all_cells();

    int current_mine_index = 0;
    int total_cells = game_matrix->get_num_rows() * game_matrix->get_num_cols();

    // variable to store time when game ends
    int final_time = 0.0;
    bool timer_stopped = false;  // time stopper
    bool timer_started = false;  // time starter
    bool show_popup = false;

    // load font for timer
    Font timer_font;
    if(!timer_font.loadFromFile(ASSETS_PATH + "monospace.ttf")) {
        return;
    }

    // int previousCellIdx = -1;
    while(game_window->isOpen()) {
        Event event;
        while(game_window->pollEvent(event)) {

            Vector2i mouse_pos = Mouse::getPosition(*game_window);
            Vector2f world_pos = game_window->mapPixelToCoords(mouse_pos);
            int cell_index_x = world_pos.x / CELL_SIZE;
            int cell_index_y = world_pos.y / CELL_SIZE;
            int cell_index = cell_index_y * game_matrix->get_num_cols() + cell_index_x;
            // Cell* cell = nullptr;

            // if (cell_index >= 0 && cell_index < total_cells) {
            //     cell = game_matrix->get_matrix()[cell_index];
            // }
            if(event.type == Event::Closed) {
                game_window->close();
            } else if(event.type == Event::MouseButtonReleased && !game_matrix->get_gameover()) {

                // ensuring clicking progress bar doesn't cause errors
                if(total_cells > cell_index) {
                    if(event.mouseButton.button == Mouse::Left) {
                        // start the timer on first click
                        if(!timer_started) {
                            game_timer.restart();  // reset timer
                            timer_started = true;  // update timer state
                        }

                        if(is_first_click) {
                            check_first_click(cell_index_x, cell_index_y);
                        }

                        game_matrix->get_matrix()[cell_index]->reveal(game_matrix);
                    } else if(event.mouseButton.button == Mouse::Right) {
                        if(!timer_started) {
                            game_timer.restart();  // reset timer
                            timer_started = true;  // update timer state
                        }
                        game_matrix->get_matrix()[cell_index]->flag(game_window);
                    }
                }
            } else if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                delete game_matrix;
                game_matrix = nullptr;
                return;
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
        int revealed_cells = game_matrix->get_revealed_cells();
        float reveal_percentage = (float)revealed_cells / (total_cells * (1 - mine_percentage));
        reveal_percentage = min(reveal_percentage, 1.0f);
        progress_bar.setSize(Vector2f(game_window->getSize().x / 4 * reveal_percentage, 20));

        // draw on window
        game_window->clear();

        // timer settings
        int elapsed = (int)(game_timer.getElapsedTime().asSeconds());
        string timer_text;

        if(!timer_started) {
            timer_text = "Time: 0s";  // display 0 if not started
        } else if(!game_matrix->get_gameover() && !check_game_win()) {
            final_time = elapsed;  // update time till game running
            timer_text = "Time: " + to_string(final_time) + "s";
        } else if(game_matrix->get_gameover() || check_game_win()) {
            timer_stopped = true;  // stop timer once game over
        }

        if(timer_stopped) {
            timer_text = "Time: " + to_string(final_time) + "s";  // display final time
        }

        // displaying timer
        Text timer_display(timer_text, timer_font);
        timer_display.setCharacterSize(20);
        timer_display.setFillColor(Color::White);
        timer_display.setPosition((game_window->getSize().x * 3 / 25), CELL_SIZE * game_matrix->get_num_rows() + 12.5);

        // if game end, reveal mines with animation
        if(game_matrix->get_gameover()) {
            if(play_animation()) {
                display_popup(false);

                delete game_matrix;
                game_matrix = nullptr;
                return;
            }
        }
        if(check_game_win()) {
            if(play_animation()) {
                int score = (game_matrix->get_num_mines() * 1000) / final_time;

                string difficulty;
                if(mine_percentage == PERCENTAGE_MINES_EASY) {
                    difficulty = "Easy";
                } else if(mine_percentage == PERCENTAGE_MINES_MEDIUM) {
                    difficulty = "Medium";
                } else if(mine_percentage == PERCENTAGE_MINES_HARD) {
                    difficulty = "Hard";
                }

                string user_name = ask_for_username(game_window);

                append_stats(user_name, score, final_time, difficulty);
                display_popup(true);
                delete game_matrix;
                game_matrix = nullptr;
                return;
            }
        }

        game_window->draw(extra_bg);
        game_window->draw(timer_display);
        game_window->draw(progress_bar_bg);
        game_window->draw(progress_bar);
        game_matrix->display(game_window);
        game_window->display();
    }

    delete game_matrix;
}

string Game::ask_for_username(RenderWindow* window) {
    string player_name = "";

    // loading font
    Font font;
    if(!font.loadFromFile(ASSETS_PATH + "monospace.ttf")) {
        return "";
    }

    // ask for name
    Text instruction("Enter your name:", font, 30);
    instruction.setFillColor(Color::White);
    instruction.setPosition(100, 150);

    // text input field
    RectangleShape input_box(Vector2f(300, 50));
    input_box.setFillColor(Color::White);
    input_box.setPosition(100, 250);

    Text input_text("", font, 30);
    input_text.setFillColor(Color::Black);
    input_text.setPosition(110, 255);  // inside the input box

    bool is_running = true;
    while(is_running && window->isOpen()) {
        Event event;
        while(window->pollEvent(event)) {
            if(event.type == Event::Closed) {
                window->close();
            }

            if(event.type == Event::TextEntered) {
                if(event.text.unicode == '\b' && !player_name.empty()) {
                    // backspace key to remove last character
                    player_name.pop_back();
                } else if(event.text.unicode < 128 && event.text.unicode != '\b') {
                    char enteredChar = (char)(event.text.unicode);

                    // ignore commas, newlines
                    if(enteredChar != ',' && enteredChar != '\n' && enteredChar != '\r') {
                        player_name += enteredChar;
                    }
                }
                input_text.setString(player_name);
            }

            // submit name
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
                is_running = false;  // Exit loop after name is entered
            }
        }

        window->clear(Color(50, 50, 50));
        window->draw(instruction);
        window->draw(input_box);
        window->draw(input_text);
        window->display();
    }

    // linking to csv
    if(!player_name.empty()) {
        return player_name;
    }

    return "anonymous";  // if no name entered, return anonymous
}

// function to display stats
void Game::display_stats(RenderWindow* window) {
    // loading font
    Font font;
    if(!font.loadFromFile(ASSETS_PATH + "monospace.ttf")) {
        return;
    }

    // button to go back
    RectangleShape back_button(Vector2f(75, 50));
    back_button.setFillColor(BUTTON_COLOR);
    back_button.setPosition(850, 650);
    back_button.setOutlineThickness(2);
    back_button.setOutlineColor(Color::White);

    // label for back button
    Text back_text;
    back_text.setFont(font);
    back_text.setString("Back");
    back_text.setCharacterSize(18);
    back_text.setFillColor(Color::Black);
    back_text.setPosition(back_button.getPosition().x + 15, back_button.getPosition().y + 15);

    // importing csv
    ifstream file(USERDATA_FILE);
    if(!file.is_open()) {
        return;
    }

    string line;
    vector<string> names, scores, time_takens, difficulties;

    // // skip first line
    getline(file, line);

    // reading csv and pushing to corresponding vectors
    while(getline(file, line)) {
        istringstream ss(line);
        string name, score, time_taken, difficulty;

        getline(ss, name, ',');
        getline(ss, score, ',');
        getline(ss, time_taken, ',');
        getline(ss, difficulty, ',');

        names.push_back(name);
        scores.push_back(score);
        time_takens.push_back(time_taken);
        difficulties.push_back(difficulty);
    }

    file.close();

    // settings headers
    vector<string> headers = {"Username", "Score", "Time Taken", "Difficulty"};

    // 2D vector for data
    vector<vector<string>> data;
    for(int i = 0; i < names.size(); ++i) {
        data.push_back({names[i], scores[i], time_takens[i], difficulties[i]});
    }

    // only show latest 15 entries
    if(data.size() > 15) {
        data = vector<vector<string>>(data.end() - 15, data.end());
    }

    // only show latest 15 entries
    if(data.size() > 15) {
        data = vector<vector<string>>(data.end() - 15, data.end());
    }

    // get max width of each col
    vector<int> col_widths(headers.size(), 0);
    for(int i = 0; i < headers.size(); ++i) {
        col_widths[i] = headers[i].length();
    }
    for(auto& row : data) {
        for(int i = 0; i < row.size(); ++i) {
            if(row[i].length() > col_widths[i]) {
                col_widths[i] = row[i].length();
            }
        }
    }

    // adding padding
    for(int i = 0; i < col_widths.size(); ++i) {
        col_widths[i] += 2;
    }

    // total table width used for centering
    int total_table_width = 0;
    for(int width : col_widths) {
        total_table_width += width;
    }
    total_table_width += (headers.size() - 1) * 10;

    // calculating offset to centre align table
    int x_offset = 100;  //(windowWidth - total_table_width) / 2 - total_table_width;

    vector<Text> texts;

    // function to create borders
    auto create_border = [&](wstring left, wstring mid, wstring right) {
        wstring border = left;
        for(int i = 0; i < col_widths.size(); ++i) {
            border += wstring(col_widths[i], L'─');
            if(i != col_widths.size() - 1) {
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
    for(int i = 0; i < headers.size(); ++i) {
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
    for(int i = 0; i < data.size(); ++i) {
        wstring row = L"│";
        for(int j = 0; j < data[i].size(); ++j) {
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
    while(window->isOpen()) {
        Event event;
        window->clear();

        for(int i = 0; i < texts.size(); ++i) {
            window->draw(texts[i]);
        }

        while(window->pollEvent(event)) {
            if(event.type == Event::Closed) {
                window->close();

            } else if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2i mousePos = Mouse::getPosition(*window);
                Vector2f worldPos = window->mapPixelToCoords(mousePos);

                // action if back button is clicked
                if(back_button.getGlobalBounds().contains(worldPos)) {
                    return;
                }
            }
        }
        window->draw(back_button);
        window->draw(back_text);
        window->display();
    }
}

void Game::main_menu(RenderWindow* window) {
    // main menu window (fixed size)
    game_window->create(VideoMode(1000, 750), "Main Menu", Style::Titlebar | Style::Close);

    // loading fonts
    Font font;
    if(!font.loadFromFile(ASSETS_PATH + "8bit.ttf")) {
        return;
    }

    Font font1;
    if(!font1.loadFromFile(ASSETS_PATH + "monospace.ttf")) {
        return;
    }

    // gif1 frames
    Texture gif1_textures[20];
    for(int i = 0; i < 20; ++i) {
        if(!gif1_textures[i].loadFromFile(ASSETS_PATH + "gif1/g1f" + to_string(i + 1) + ".png")) {
            return;
        }
    }

    // gif2 frames
    Texture gif2_textures[20];
    for(int i = 0; i < 20; ++i) {
        if(!gif2_textures[i].loadFromFile(ASSETS_PATH + "gif2/g2f" + to_string(i + 1) + ".png")) {
            return;
        }
    }

    // help images
    Texture help_images[4];
    for(int i = 0; i < 4; ++i) {
        if(!help_images[i].loadFromFile(ASSETS_PATH + "help/h" + to_string(i + 1) + ".png")) {
            return;
        }
    }

    // Creating buttons
    RectangleShape play_button(Vector2f(175, 75));
    play_button.setFillColor(BUTTON_COLOR);
    play_button.setPosition(500, 300);
    play_button.setOutlineThickness(2);
    play_button.setOutlineColor(Color::White);

    // Difficulty buttons (for difficulty selection screen)
    RectangleShape easy_button(Vector2f(250, 75));
    easy_button.setFillColor(BUTTON_COLOR);
    easy_button.setPosition(600, 300);
    easy_button.setOutlineThickness(2);
    easy_button.setOutlineColor(Color::White);

    RectangleShape medium_button(Vector2f(250, 75));
    medium_button.setFillColor(BUTTON_COLOR);
    medium_button.setPosition(600, 400);
    medium_button.setOutlineThickness(2);
    medium_button.setOutlineColor(Color::White);

    RectangleShape hard_button(Vector2f(250, 75));
    hard_button.setFillColor(BUTTON_COLOR);
    hard_button.setPosition(600, 500);
    hard_button.setOutlineThickness(2);
    hard_button.setOutlineColor(Color::White);

    RectangleShape help_button(Vector2f(175, 75));
    help_button.setFillColor(Color(BUTTON_COLOR));
    help_button.setPosition(625, 425);
    help_button.setOutlineThickness(2);
    help_button.setOutlineColor(Color::White);

    RectangleShape stats_button(Vector2f(200, 75));
    stats_button.setFillColor(BUTTON_COLOR);
    stats_button.setPosition(750, 550);
    stats_button.setOutlineThickness(2);
    stats_button.setOutlineColor(Color::White);

    RectangleShape next_button(Vector2f(75, 50));
    next_button.setFillColor(BUTTON_COLOR);
    next_button.setPosition(850, 650);
    next_button.setOutlineThickness(2);
    next_button.setOutlineColor(Color::White);

    // Labels
    Text play_text, help_text, stats_text, next_text, easy_text, medium_text, hard_text;
    ;
    play_text.setFont(font);
    play_text.setString("Play");
    play_text.setCharacterSize(30);
    play_text.setFillColor(Color::Black);
    play_text.setPosition(play_button.getPosition().x + 30, play_button.getPosition().y + 25);

    easy_text.setFont(font);
    easy_text.setString("Easy");
    easy_text.setCharacterSize(30);
    easy_text.setFillColor(Color::Black);
    easy_text.setPosition(easy_button.getPosition().x + 60, easy_button.getPosition().y + 25);

    medium_text.setFont(font);
    medium_text.setString("Medium");
    medium_text.setCharacterSize(30);
    medium_text.setFillColor(Color::Black);
    medium_text.setPosition(medium_button.getPosition().x + 40, medium_button.getPosition().y + 25);

    hard_text.setFont(font);
    hard_text.setString("Hard");
    hard_text.setCharacterSize(30);
    hard_text.setFillColor(Color::Black);
    hard_text.setPosition(hard_button.getPosition().x + 60, hard_button.getPosition().y + 25);

    help_text.setFont(font);
    help_text.setString("Help");
    help_text.setCharacterSize(30);
    help_text.setFillColor(Color::Black);
    help_text.setPosition(help_button.getPosition().x + 30, help_button.getPosition().y + 25);

    stats_text.setFont(font);
    stats_text.setString("Stats");
    stats_text.setCharacterSize(30);
    stats_text.setFillColor(Color::Black);
    stats_text.setPosition(stats_button.getPosition().x + 30, stats_button.getPosition().y + 25);

    next_text.setFont(font1);
    next_text.setString("Next");
    next_text.setCharacterSize(18);
    next_text.setFillColor(Color::Black);
    next_text.setPosition(next_button.getPosition().x + 15, next_button.getPosition().y + 15);

    // Status
    bool is_playing = false;
    bool selecting_difficulty = false;
    bool in_menu = true;
    bool in_help = false;
    int currentImageIndex = 0;

    // Frame timing
    float frame_duration = 0.1f;
    Clock frame_clock;
    int current_frame = 0;  // Index for current frame
    bool first_gif_finished = false;

    // while user on main menu window
    while(window->isOpen()) {
        Event event;
        while(window->pollEvent(event)) {
            if(event.type == Event::Closed) {
                window->close();
            }

            if(in_menu && !is_playing) {
                Vector2i mouse_pos = Mouse::getPosition(*window);

                // hover effect
                if(play_button.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
                    play_button.setFillColor(Color(BUTTON_COLOR));
                    play_button.setOutlineColor(Color::Black);
                } else {
                    play_button.setFillColor(
                        Color(BUTTON_COLOR.r - 30, BUTTON_COLOR.g - 10, BUTTON_COLOR.b - 10));  // decrease brightness
                    play_button.setOutlineColor(Color::White);
                }

                if(help_button.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
                    help_button.setFillColor(Color(BUTTON_COLOR));
                    help_button.setOutlineColor(Color::Black);
                } else {
                    help_button.setFillColor(
                        Color(BUTTON_COLOR.r - 30, BUTTON_COLOR.g - 10, BUTTON_COLOR.b - 10));  // decrease brightness
                    help_button.setOutlineColor(Color::White);
                }

                if(stats_button.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
                    stats_button.setFillColor(Color(BUTTON_COLOR));
                    stats_button.setOutlineColor(Color::Black);
                } else {
                    stats_button.setFillColor(
                        Color(BUTTON_COLOR.r - 30, BUTTON_COLOR.g - 10, BUTTON_COLOR.b - 10));  // decrease brightness
                    stats_button.setOutlineColor(Color::White);
                }

                // button controls
                if(event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                    if(play_button.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
                        // ask_for_username(window);
                        selecting_difficulty = true;
                        // is_playing = true;
                        in_menu = false;
                    } else if(help_button.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
                        in_help = true;  // show help page
                        in_menu = false;
                    } else if(stats_button.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
                        display_stats(window);
                    }
                }
            }

            // changing help instruction images
            if(in_help && event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                Vector2i mouse_pos = Mouse::getPosition(*window);
                if(next_button.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
                    currentImageIndex++;
                    if(currentImageIndex == 4) {
                        currentImageIndex = 0;
                        in_help = false;
                        in_menu = true;
                    }
                }
            }
        }

        // Difficulty selection screen
        if(selecting_difficulty) {
            Vector2i mouse_pos = Mouse::getPosition(*window);

            // hover effect
            if(easy_button.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
                easy_button.setFillColor(Color(BUTTON_COLOR));
                easy_button.setOutlineColor(Color::Black);
            } else {
                easy_button.setFillColor(
                    Color(BUTTON_COLOR.r - 30, BUTTON_COLOR.g - 10, BUTTON_COLOR.b - 10));  // Decrease brightness
                easy_button.setOutlineColor(Color::White);
            }

            if(medium_button.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
                medium_button.setFillColor(Color(BUTTON_COLOR));
                medium_button.setOutlineColor(Color::Black);
            } else {
                medium_button.setFillColor(
                    Color(BUTTON_COLOR.r - 30, BUTTON_COLOR.g - 10, BUTTON_COLOR.b - 10));  // Decrease brightness
                medium_button.setOutlineColor(Color::White);
            }

            if(hard_button.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
                hard_button.setFillColor(Color(BUTTON_COLOR));
                hard_button.setOutlineColor(Color::Black);
            } else {
                hard_button.setFillColor(
                    Color(BUTTON_COLOR.r - 30, BUTTON_COLOR.g - 10, BUTTON_COLOR.b - 10));  // Decrease brightness
                hard_button.setOutlineColor(Color::White);
            }

            // select difficutly based on button
            if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                if(easy_button.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
                    mine_percentage = PERCENTAGE_MINES_EASY;
                    is_playing = true;
                    selecting_difficulty = false;
                }
                if(medium_button.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
                    mine_percentage = PERCENTAGE_MINES_MEDIUM;
                    is_playing = true;
                    selecting_difficulty = false;
                }
                if(hard_button.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
                    mine_percentage = PERCENTAGE_MINES_HARD;
                    is_playing = true;
                    selecting_difficulty = false;
                }
            }
        }

        // update current frame
        if(frame_clock.getElapsedTime().asSeconds() >= frame_duration) {
            if(!first_gif_finished) {
                current_frame++;
                if(current_frame >= 20) {
                    current_frame = 0;          // reset for 2nd gif
                    first_gif_finished = true;  // 1st gif done
                }
            } else {
                current_frame = (current_frame + 1) % 20;  // loop for 2nd gif
            }
            frame_clock.restart();  // keep playing 2nd gif
        }

        window->clear(MAIN_BG_COLOR);

        // Draw gif frames
        Sprite background_sprite;
        if(!first_gif_finished) {
            background_sprite.setTexture(gif1_textures[current_frame]);  // Draw 1st gif
        } else {
            background_sprite.setTexture(gif2_textures[current_frame]);  // Draw 2nd gif
        }
        window->draw(background_sprite);

        // Draw everything else
        if(in_menu) {
            window->draw(play_button);
            window->draw(play_text);
            window->draw(help_button);
            window->draw(help_text);
            window->draw(stats_button);
            window->draw(stats_text);
        } else if(in_help) {
            Sprite help_sprite;
            help_sprite.setTexture(help_images[currentImageIndex]);
            window->draw(help_sprite);

            window->draw(next_button);
            window->draw(next_text);
        } else if(selecting_difficulty) {
            window->draw(easy_button);
            window->draw(easy_text);
            window->draw(medium_button);
            window->draw(medium_text);
            window->draw(hard_button);
            window->draw(hard_text);
        }

        window->display();

        if(is_playing) {
            run();
            in_menu = true;
            is_playing = false;
        }
    }
}

void Game::append_stats(string username, int score, int time_taken, string difficulty) {
    // open file and append game stats to csv file
    ofstream stats_file;
    stats_file.open(USERDATA_FILE, ios::app);
    stats_file << username << "," << score << "," << time_taken << "," << difficulty << endl;
    stats_file.close();
}

void Game::check_first_click(int cell_index_x, int cell_index_y) {
    set_is_first_click(false);  // setting the first clisck as false

    game_matrix->first_click(cell_index_x, cell_index_y);
}

bool Game::play_animation() {
    static Clock clock;
    static int current_mine_index = 0;

    if(current_mine_index < game_matrix->get_mine_locations().size()) {
        if(clock.getElapsedTime().asMilliseconds() >=
           (ANIMATION_DURATION / (game_matrix->get_num_cols() * game_matrix->get_num_rows() * mine_percentage))) {
            int location = game_matrix->get_mine_locations()[current_mine_index];
            Cell* mine = game_matrix->get_matrix()[location];

            if(game_matrix->get_gameover()) {
                if(!mine->get_is_reveal()) {
                    if(mine->get_is_flagged()) {
                        mine->flag(game_window);
                    }
                    mine->reveal(game_matrix);
                }
            } else if(check_game_win()) {
                if(!mine->get_is_reveal()) {
                    mine->set_color(Color::White);
                }
            }

            current_mine_index++;
            clock.restart();
        }
    }

    // check if all mines revealed
    if(current_mine_index >= game_matrix->get_mine_locations().size()) {
        current_mine_index = 0;
        return true;
    }

    return false;
}

void Game::display_popup(bool game_status) {
    // Load font
    Font font;
    if(!font.loadFromFile(ASSETS_PATH + "monospace.ttf")) {
        return;
    }

    // transparent bg for popup
    RectangleShape popup_bg(Vector2f(game_window->getSize().x / 2, game_window->getSize().y / 3));
    popup_bg.setFillColor(Color(0, 0, 0, 150));
    popup_bg.setPosition(game_window->getSize().x / 4, game_window->getSize().y / 3);

    // create text for the win/loss message
    Text result_text;
    result_text.setFont(font);
    result_text.setCharacterSize(40);

    if(game_status) {
        result_text.setString("You Win!");
        result_text.setFillColor(Color::Green);
    } else if(!game_status) {
        result_text.setString("Game Over");
        result_text.setFillColor(Color::Red);
    }

    // center text
    FloatRect textRect = result_text.getLocalBounds();
    result_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    result_text.setPosition(game_window->getSize().x / 2.0f, game_window->getSize().y / 2.5f);

    // return button
    RectangleShape return_button(Vector2f(300, 50));
    return_button.setFillColor(Color(50, 150, 50));
    return_button.setPosition(game_window->getSize().x / 2.0f - 150, game_window->getSize().y / 2.0f);

    // label for button
    Text return_text;
    return_text.setFont(font);
    return_text.setCharacterSize(30);
    return_text.setString("Return to Menu");
    return_text.setFillColor(Color::White);

    FloatRect return_text_rect = return_text.getLocalBounds();
    return_text.setOrigin(return_text_rect.left + return_text_rect.width / 2.0f,
                          return_text_rect.top + return_text_rect.height / 2.0f);
    return_text.setPosition(return_button.getPosition().x + return_button.getSize().x / 2,
                            return_button.getPosition().y + return_button.getSize().y / 2);

    // Popup display and event handling loop
    bool popup_active = true;
    while(popup_active) {
        Event event;
        while(game_window->pollEvent(event)) {
            if(event.type == Event::Closed) {
                game_window->close();
                return;
            }

            if(event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                Vector2i mousePos = Mouse::getPosition(*game_window);

                // if the button is clicked, do action
                if(return_button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    popup_active = false;  // Exit the popup loop
                    return;
                }
            }
        }

        game_window->clear();
        game_matrix->display(game_window);

        // Draw popup elements
        game_window->draw(popup_bg);
        game_window->draw(result_text);
        game_window->draw(return_button);
        game_window->draw(return_text);

        game_window->display();
    }
}

bool Game::check_game_win() {

    if(game_matrix->get_revealed_cells() ==
       ((game_matrix->get_num_cols() * game_matrix->get_num_rows()) - game_matrix->get_num_mines())) {
        return true;
    }

    return false;
}

// getters and setters
// get game window
RenderWindow* Game::get_game_window() {
    return this->game_window;
}

// get game matrix
CellMatrix* Game::get_game_matrix() {
    return this->game_matrix;
}

bool Game::get_is_first_click() {
    return is_first_click;
}

// set game window manually
void Game::set_game_window(RenderWindow* game_window) {
    this->game_window = game_window;
};

// set game matrix manually
void Game::set_game_matrix(CellMatrix* game_matrix) {
    this->game_matrix = game_matrix;
}
void Game::set_is_first_click(bool is_first_click) {
    this->is_first_click = is_first_click;
};

// destroy all attached objects
Game::~Game() {
    delete game_window;
    // delete game_matrix;
}
