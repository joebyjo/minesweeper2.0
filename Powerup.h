#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Number.h"

using namespace sf;
using namespace std;

class CellMatrix;

class Powerup: public Number{

    protected:

    public:
        Powerup(int x, int y); // constructor

        void on_revealed(CellMatrix *game_matrix);
        void supernumber(CellMatrix* game_matrix); // flags the mine in the radius of 3 X 3
        void xray(CellMatrix* game_matrix); // blinks the matrix for one sec
        
        // destructor
        ~Powerup();
        
};

#endif