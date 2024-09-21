#ifndef MINE_H
#define MINE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Cell.h"

using namespace sf;
using namespace std;

class Mine: public Cell{

    protected:


    public:
        Mine(int x, int y); // constructor
        
        void unique_function(); // owriting function

        
};

#endif