#include "Empty.h"
#include "CellMatrix.h"
#include "Constants.h"

Empty::Empty(int x, int y) : Cell(x, y) {

    // alternating colors of empty cells
    if(((x % 2 == 0) && (y % 2 == 0)) || ((x % 2 == 1) && (y % 2 == 1))) {
        this->color = EMPTY_COLOR_DARK;
    } else {
        this->color = EMPTY_COLOR_LIGHT;
    }

    this->type = "empty";
}

void Empty::on_revealed(CellMatrix* game_matrix) {

    int index_temp = 0;

    for(int row = this->location[1] - 1; (row < this->location[1] + 2) && (row < game_matrix->get_num_rows()); row++) {
        for(int col = this->location[0] - 1; (col < this->location[0] + 2) && (col < game_matrix->get_num_cols());
            col++) {

            // checking the cell doesn't got out of game board 0,0
            if(row < 0 || col < 0) {
                continue;
            }

            // storing the index of cell in it
            index_temp = row * game_matrix->get_num_cols() + col;

            if((game_matrix->get_matrix()[index_temp])->get_type() != "mine" &&
               (game_matrix->get_matrix()[index_temp])->get_type() != "powerup") {
                game_matrix->get_matrix()[index_temp]->reveal(game_matrix);
            }
        }
    }
}
