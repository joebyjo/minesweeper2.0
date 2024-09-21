#include "Empty.h"
#include "Constants.h"

Empty::Empty(int x, int y): Cell(x, y) {
    this->color = EMPTY_COLOR_DARK;
}

void Empty::unique_function() {}