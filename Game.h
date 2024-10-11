#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "CellMatrix.h"
#include "Cell.h"
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
        void mainMenu(sf::RenderWindow* window);

        bool check_game_win();

        // getters and setters
        RenderWindow* get_game_window();
        CellMatrix* get_game_matrix();
        
        void set_game_window(RenderWindow* game_window);
        void set_game_matrix(CellMatrix* game_matrix);

        ~Game();

        
};

#endif