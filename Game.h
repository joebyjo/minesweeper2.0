#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "CellMatrix.h"
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

class Game{

    protected:
        RenderWindow *game_window;
        CellMatrix *game_matrix;

    public:
        Game(int num_cols, int num_rows);
        void run();

        ~Game();

        
};

#endif