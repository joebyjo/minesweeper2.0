
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
        bool is_first_click;
        Clock game_timer;
        bool hasStarted;

    public:
        Game(int num_cols, int num_rows);
        void run();
        void check_first_click(int cell_index_x, int cell_index_y);
        void mainMenu(sf::RenderWindow* window);


        // getters and setters
        RenderWindow* get_game_window();
        CellMatrix* get_game_matrix();
        bool get_is_first_click();
        
        void set_game_window(RenderWindow* game_window);
        void set_game_matrix(CellMatrix* game_matrix);
        void set_is_first_click(bool is_first_click);

        ~Game();

        
};

#endif