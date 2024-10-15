#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <SFML/Graphics.hpp>
#include <ctime>

using namespace std;
using namespace sf;

// length of side of cell
const int CELL_SIZE = 50;

// dimension of game board
const int NUM_OF_ROWS = 14;
const int NUM_OF_COLS = 20;

// number of mines
const float PERCENTAGE_MINES_EASY = 0.1;
const float PERCENTAGE_MINES_MEDIUM = 0.15;
const float PERCENTAGE_MINES_HARD = 0.25;

// duration of animation in milliseconds
const float ANIMATION_DURATION = 3000;

// duration of Xray
const int XRAY_DURATION = 2000;

// number of Powerups in the game
const int NUM_POWERUPS = 1;

// padding
const float NUMBER_CELL_PADDING = 7.5;

// title of window
const string WINDOW_TITLE = "MINESWEEPER";

// random seed
const int RANDOM_SEED = time(0);

// Colors
const Color CELL_COLOR_1 = Color(170, 215, 81);
const Color CELL_COLOR_2 = Color(147, 203, 57);
const Color EMPTY_COLOR_LIGHT = Color(229,194,159);
const Color EMPTY_COLOR_DARK = Color(215,184,153);
const Color NUMBER_COLOR = Color(0, 0, 255);
const Color MINE_COLOR = Color(255, 0, 0);
const Color POWERUP_COLOR = Color(255, 215, 0);

const Color MAIN_BG_COLOR = Color(170, 215, 81);
const Color BUTTON_COLOR = Color(102, 178, 225);
// Assets path
const string ASSETS_PATH = "assets/";
const string USERDATA_FILE = "game_stats.csv";

#endif