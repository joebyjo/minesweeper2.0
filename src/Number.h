#ifndef NUMBER_H
#define NUMBER_H

#include "Cell.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class CellMatrix;

class Number : public Cell {

    protected:
        Texture number_texture;
        Sprite* number_cell;
        int neighboring_mine_count;

    public:
        Number(int x, int y);  // constructor

        void increment_mine_count();
        void decrement_mine_count();
        void draw(RenderWindow* game_window);
        void on_revealed(CellMatrix* game_matrix);  // owriting function

        // getters and setters
        Texture get_number_texture();
        Sprite* get_number_cell();
        int get_neighboring_mine_count();

        void set_number_texture(Texture number_texture);
        void set_number_cell(Sprite* number_cell);
        void set_neighboring_mine_count(int neighboring_mine_count);

        // destructor
        ~Number();
};

#endif