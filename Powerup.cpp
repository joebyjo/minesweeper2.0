#include "Powerup.h"
#include "Constants.h"
#include "CellMatrix.h"

Powerup::Powerup(int x, int y): Number(x, y) {
    this->color = POWERUP_COLOR;
    this->type = "powerup"; 
}

// on_revealed function a vortual void function
void Powerup::on_revealed(CellMatrix* game_matrix) {
    supernumber(game_matrix);
}
void Powerup::supernumber(CellMatrix* game_matrix) {

    int index_temp = 0;

    for (int row  = this->location[1] - 1; (row < this->location[1] + 2) && (row < game_matrix->get_num_rows()); row++){
        for (int col = this->location[0] - 1; (col < this->location[0] + 2) && (col < game_matrix->get_num_cols()); col++){
            
            // checking the cell doesn't got out of game board 0,0
            if (row < 0 || col < 0){
                continue;
            }

             // storing the index of cell in it
            index_temp = row * game_matrix->get_num_cols() + col;

            if ((game_matrix->get_matrix()[index_temp])->get_type() == "mine" && !(game_matrix->get_matrix()[index_temp])->get_is_flagged()){
                game_matrix->get_matrix()[index_temp]->flag(game_matrix->get_game_window());
            }
            
        }
    }
}

void Powerup::xray(CellMatrix* game_matrix) {
    // game_matrix->reveal_all_cells();
    // game_matrix->get_game_window()->clear();
    // game_matrix->display();
}

Powerup::~Powerup() {}
