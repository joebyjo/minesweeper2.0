#include "Cell.h"

Cell::Cell(int size, int x, int y){

    cell = new RectangleShape();

    // creating location array to store the location of cell
    this->location = new int[2];
    this->location[0] = x;
    this->location[1] = y;

    // saving the color into variable color
    this->color = Color::Green;

    cell->setSize(Vector2f(size, size));
    cell->setPosition(location[0], location[1]);
    cell->setFillColor(color);
    cell->setOrigin(location[0] / 2, location[1] / 2);
}

void Cell::draw(RenderWindow *game_matrix) {
    game_matrix->draw(*cell);
}

void Cell::set_color(Color color) {
    this->color = color;
    cell->setFillColor(this->color);
}
