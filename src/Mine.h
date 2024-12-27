#ifndef MINE_H
#define MINE_H

#include "Cell.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class CellMatrix;

using namespace sf;
using namespace std;

class Mine : public Cell {

    protected:
        Texture mine_texture;
        Sprite mine_cell;

    public:
        Mine(int x, int y);  // constructor

        void draw(RenderWindow* game_window);
        void on_revealed(CellMatrix* game_matrix);  // owriting function
        void delete_mine(CellMatrix* game_matrix);  // deleting the mine
        void peek(RenderWindow* game_window);       // for the xray function
};

#endif