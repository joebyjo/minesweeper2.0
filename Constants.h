#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

// length of side of cell
const int CELL_SIZE = 50;

// dimension of game board
const int NUM_OF_ROWS = 15;
const int NUM_OF_COLS = 20;

// number of cells
const int NUM_OF_CELLS = NUM_OF_ROWS * NUM_OF_COLS;

// number of mines
const int NUM_OF_MINES = NUM_OF_CELLS * 0.1;


// title of window
const string WINDOW_TITLE = "MINESWEEPER";

// Colors
const Color CELL_COLOR_1 = Color(170, 215, 81);
const Color CELL_COLOR_2 = Color(147, 203, 57);
const Color EMPTY_COLOR_LIGHT = Color(0, 0, 0);
const Color EMPTY_COLOR_DARK = Color(0, 255, 0);
const Color NUMBER_COLOR = Color(0, 0, 255);
const Color MINE_COLOR = Color(255, 0, 0);

#endif