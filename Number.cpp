#include "Number.h"
#include "Constants.h"
#include "CellMatrix.h"

Number::Number(int x, int y): Cell(x, y) {
    this->color = NUMBER_COLOR;
    this->type = "number";
}

void Number::on_revealed(CellMatrix* game_matrix) {}