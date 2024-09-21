#ifndef EMPTY_H
#define EMPTY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Cell.h"

using namespace sf;
using namespace std;

class Empty: public Cell{

    protected:


    public:
        Empty(int x, int y); // constructor
        
        void unique_function(); // owriting function

        
};

#endif