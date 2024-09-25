#include "Empty.h"
#include "Constants.h"

Empty::Empty(int x, int y): Cell(x, y) {

    // alternating colors of empty cells
    if (((x%2== 0) && (y%2==0)) || ((x%2==1) && (y%2==1))){ 
        this->color = EMPTY_COLOR_DARK; } 
    else { 
        this->color = EMPTY_COLOR_LIGHT; } 
        
    this->type = "empty";
}

void Empty::on_revealed(CellMatrix* game_matrix) {

    int index_temp = 0;
    string type_temp = "\0";
    for (int i  = -1; i < 2 && !(location[1] + i > game_matrix->get_num_rows() - 1); i++){
        for (int j = -1; j < 2 && !(location[0] + i > game_matrix->get_num_cols() - 1); j++){
            
            // checking the cell doesn't got out of game board
            if (!(location[1] + i < 0) || !(location[0] + j < 0)){
                continue;
            }

             // storing the type of cell in it
            index_temp = (this->location[1] + i) * game_matrix->get_num_cols() + (this->location[0] + j);
            type_temp = (game_matrix->get_matrix()[index_temp])->get_type();

            if (type == "empty"){
                game_matrix->get_matrix()[index_temp]->reveal(game_matrix);
            }
            else if(type == "number"){
                game_matrix->get_matrix()[index_temp]->reveal(game_matrix);
            }
            
        }
    }
}
