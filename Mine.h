#ifndef MINE_H
#define MINE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Cell.h"

class CellMatrix;

using namespace sf;
using namespace std;

class Mine: public Cell{

    protected:


    public:
        Mine(int x, int y); // constructor
        
        void on_revealed(CellMatrix *game_matrix); // owriting function
        void delete_mine(CellMatrix *game_matrix); // deleting the mine

        
};

#endif