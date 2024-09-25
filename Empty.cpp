#include "Empty.h"
#include "Constants.h"

Empty::Empty(int x, int y): Cell(x, y) {

    // alternating colors of empty cells
    if (((x%2== 0) && (y%2==0)) || ((x%2==1) && (y%2==1))){ 
        this->color = EMPTY_COLOR_DARK; } 
    else { 
        this->color = EMPTY_COLOR_LIGHT; } 
    
}

void Empty::unique_function() {}