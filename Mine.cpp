#include "Mine.h"
#include "Constants.h"
#include "CellMatrix.h"
#include <vector>

Mine::Mine(int x, int y): Cell(x, y) {
    this->color = MINE_COLOR;
    this->type = "mine";
}

// function that runs when the cell is revealed
void Mine::on_revealed(CellMatrix* game_matrix) {

    // deleting the mine from the game
    this->delete_mine(game_matrix);
     
    // calling the game over function
    game_matrix->game_over();
}

void Mine::delete_mine(CellMatrix* game_matrix) {

    // finding the location of mine and deleting from array
    int cell_location = location[1] * game_matrix->get_num_cols() + location[0]; // storing the cell
    vector<int> mine_locations = game_matrix->get_mine_locations(); // storing the vector temperary

    // for loop
    for (int i = 0; i < mine_locations.size(); i++){

        if (mine_locations.at(i) == cell_location){
            // swapping the location with the last index
            swap(mine_locations.at(i), mine_locations.at(mine_locations.size() - 1));
        }
    }
    
    // setting the new vector in the cell matrix
    game_matrix->set_mine_locations(mine_locations);
    // appending the num_mines by -1
    game_matrix->set_num_mines(game_matrix->get_num_mines() - 1);

    // Testing:  cout << game_matrix->get_num_mines() << endl; 
}
