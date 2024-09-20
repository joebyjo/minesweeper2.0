#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

// length of side of cell
int CELL_SIZE = 50;

// dimension of game board
int NUM_OF_ROWS = 8;
int NUM_OF_COLS = 10;

// number of cells
int NUM_OF_CELLS = NUM_OF_ROWS * NUM_OF_COLS;

// number of mines
int NUM_OF_MINES = NUM_OF_CELLS * 0.1;


// title of window
string WINDOW_TITLE = "MINESWEEPER";

Color CELL_COLOR_1 = Color(2, 194, 15,255);
Color CELL_COLOR_2 = Color(0, 166, 11,255);



#endif