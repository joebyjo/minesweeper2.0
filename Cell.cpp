#include "Cell.h"
#include "Constants.h"

Cell::Cell(int x, int y){

    cell = new RectangleShape();

    // creating location array to store the location of cell
    this->location = new int[2];
    this->location[0] = x;
    this->location[1] = y;

    // saving the color into variable color
    this->color = CELL_COLOR_1;
    this->is_reveal = false;

    cell->setSize(Vector2f(CELL_SIZE,CELL_SIZE));
    cell->setPosition(location[0], location[1]);
    cell->setFillColor(color);
    // cell->setOutlineColor(Color:: Black);
    // cell->setOutlineThickness(1);
}

// Function to draw the cell on window
void Cell::draw(RenderWindow *game_window) {
    game_window->draw(*cell);
}

// function to reveal the color of cell
void Cell::reveal() {
    this->is_reveal = true;
    cell->setFillColor(this->color); // changing color
    this->unique_function(); // calling the unique function
}

// owritten function
void Cell::unique_function() {}


// getters and setters
// get cell
RectangleShape* Cell:: get_cell() {
    return this->cell;
 };

// get location
int* Cell:: get_location() {
    return this->location;
}

// get color
Color Cell:: get_color() {
    return this->color;
};

// set cell manually
void Cell:: set_cell(RectangleShape *cell) {
    this->cell = cell;
};

// set cell location manually
void Cell:: set_location(int *location) {
    this->location = location;
    cell->setPosition(location[0], location[1]);
};

// set cell color manually
void Cell::set_color(Color color) {
    cell->setFillColor(color);
}

// destructor to delete rectangle obj and location array
Cell:: ~Cell() {
    delete cell;
    delete[] location;
}