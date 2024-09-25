#include "Empty.h"
#include "Constants.h"

Empty::Empty(int x, int y): Cell(x, y) {

    // j*CELL_SIZE, i*CELL_SIZE
    int col = x/CELL_SIZE;
    int row = y/CELL_SIZE;

    // alternating colors of empty cells
    if (((col%2== 0) && (row%2==0)) || ((col%2==1) && (row%2==1))){ 
        this->color = EMPTY_COLOR_DARK; } 
    else { 
        this->color = EMPTY_COLOR_LIGHT; } 
    
}

void Empty::unique_function() {}