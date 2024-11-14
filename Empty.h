#ifndef EMPTY_H
#define EMPTY_H

#include "Cell.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class CellMatrix;

class Empty : public Cell {

    protected:
    public:
        Empty(int x, int y);  // constructor

        void on_revealed(CellMatrix* game_matrix);  // owriting function
};

#endif