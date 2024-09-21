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

    cell->setSize(Vector2f(50, 50));
    cell->setPosition(location[0], location[1]);
    cell->setFillColor(color);
    // cell->setOutlineColor(Color:: Black);
    // cell->setOutlineThickness(1);
}

// Function to draw the cell on window
void Cell::draw(RenderWindow *game_window) {
    game_window->draw(*cell);
}

void Cell::set_color(Color color) {
    this->color = color;
    cell->setFillColor(this->color);
}

// destructor to delete rectangle obj and location array
Cell:: ~Cell() {
    delete cell;
    delete[] location;
}