#include "Mine.h"
#include "Constants.h"
#include "CellMatrix.h"

Mine::Mine(int x, int y): Cell(x, y) {
    this->color = MINE_COLOR;
    this->type = "mine";
}

// function that runs when the cell is revealed
void Mine::on_revealed(CellMatrix* game_matrix) {

    // deleting the mine from the game
    // this->delete_mine(game_matrix);
     
    // calling the game over function
    game_matrix->game_over();
}

void Mine::delete_mine(CellMatrix* game_matrix) {

    // finding the location of mine and deleting from array
    int cell_location;
    for (int i = 0; i < game_matrix->get_num_mines(); i++){
        // storing the cell number
        cell_location = location[1] * game_matrix->get_num_cols() + location[0];

        if (game_matrix->get_mine_locations()[i] == (cell_location)){
            // swapping the location with the last index
            swap(game_matrix->get_matrix()[cell_location], game_matrix->get_matrix()[game_matrix->get_num_mines() - 1]);
        }
    }
    
    // appending the num_mines by -1
    game_matrix->set_num_mines(game_matrix->get_num_mines() - 1);
}
