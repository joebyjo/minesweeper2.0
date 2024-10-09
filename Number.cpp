#include "Number.h"
#include "Constants.h"
#include "CellMatrix.h"

Number::Number(int x, int y): Cell(x, y) {

    number_texture = Texture();
    number_cell = new Sprite();
    this->neighboring_mine_count = 1;

    number_texture.loadFromFile(ASSETS_PATH+"num"+to_string(neighboring_mine_count)+".png");
    number_cell->setTexture(number_texture);

    float padding = NUMBER_CELL_PADDING;

    // scaling to fit the sprite into the cell
    number_cell->setScale(
        (CELL_SIZE - padding) / float(number_texture.getSize().x),
        (CELL_SIZE - padding) / float(number_texture.getSize().y)
    );

    // centering the sprite within the cell
    number_cell->setPosition(
        location[0] * CELL_SIZE + (padding / 2),
        location[1] * CELL_SIZE + (padding / 2)
    );

    // alternate cell
    if (((x%2== 0) && (y%2==0)) || ((x%2==1) && (y%2==1))){ 
        this->color = EMPTY_COLOR_DARK; } 
    else { 
        this->color = EMPTY_COLOR_LIGHT; } 

    this->type = "number";
}

// increment mine_count
void Number:: increment_mine_count() {
    this->neighboring_mine_count +=1;
    number_texture.loadFromFile(ASSETS_PATH+"num"+to_string(neighboring_mine_count)+".png");
    number_cell->setTexture(number_texture);
}

// override the draw function to draw the cell and the sprite
void Number::draw(RenderWindow* game_window) {
    Cell::draw(game_window);
    if (is_reveal) {
        game_window->draw(*number_cell);
    }
}

void Number::on_revealed(CellMatrix* game_matrix) {}

// getters
Texture Number::get_number_texture() {
    return this->number_texture; 
}

Sprite* Number::get_number_cell() {
    return this->number_cell;
}

int Number::get_neighboring_mine_count() {
    return this->neighboring_mine_count;
}

// setters
void Number::set_number_texture(Texture new_texture) {
    this->number_texture = new_texture; 
}

void Number::set_number_cell(Sprite* new_number_cell) {
    this->number_cell = new_number_cell;
}

void Number::set_neighboring_mine_count(int new_neighboring_mine_count) {
    this->neighboring_mine_count = new_neighboring_mine_count;
}

Number:: ~Number() {
    delete number_cell;
}