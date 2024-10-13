#include "Powerup.h"
#include "Constants.h"
#include "Mine.h"
#include "CellMatrix.h"
#include <thread>  // for std::this_thread::sleep_for
#include <chrono>  // for std::chrono::milliseconds

Powerup::Powerup(int x, int y): Number(x, y) {
    this->color = POWERUP_COLOR;
    this->type = "powerup"; 
}

// on_revealed function a vortual void function
void Powerup::on_revealed(CellMatrix* game_matrix) {

    srand(RANDOM_SEED);
    int random = rand() % 2;

    if (random == 0){
        supernumber(game_matrix);
    } else {
        xray(game_matrix);
    }

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

    // finding the location of mine and peeking
    vector<int> mine_locations = game_matrix->get_mine_locations(); // storing the vector temperary

    // refreshing screen to display the number cell
    game_matrix->get_game_window()->clear();
    game_matrix->display(game_matrix->get_game_window());
    game_matrix->get_game_window()->display();

    // Add a delay before displaying xray affect
    std::this_thread::sleep_for(std::chrono::milliseconds(XRAY_DURATION)); // Delay of 1 second

    // for loop to reveal every mine
    for (int i : mine_locations){
        static_cast<Mine*>(game_matrix->get_matrix()[i])->peek(game_matrix->get_game_window());
    }

    // game_matrix->get_game_window()->clear();
    game_matrix->get_game_window()->display();

    // Add a delay to simulate x-ray effect
    std::this_thread::sleep_for(std::chrono::milliseconds(XRAY_DURATION)); // Delay of 1 second
}

Powerup::~Powerup() {}
