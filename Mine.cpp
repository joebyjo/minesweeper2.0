#include "Mine.h"
#include "Constants.h"
#include "CellMatrix.h"
#include <vector>

Mine::Mine(int x, int y): Cell(x, y) {
    mine_texture = Texture();
    mine_cell = Sprite();

    mine_texture.loadFromFile(ASSETS_PATH+"mine.png");
    mine_cell.setTexture(mine_texture);

    // scaling to fit the sprite into the cell
    mine_cell.setScale(
        CELL_SIZE / float (mine_texture.getSize().x),
        CELL_SIZE / float (mine_texture.getSize().y)
    );

    mine_cell.setPosition(location[0]*CELL_SIZE, location[1]*CELL_SIZE);

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

// override the draw function to draw the cell and the sprite
void Mine::draw(RenderWindow* game_window) {
    Cell::draw(game_window);
    if (is_reveal) {
        game_window->draw(mine_cell);
    }
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

void Mine::peek(RenderWindow* game_window) {
        game_window->draw(mine_cell);
}
