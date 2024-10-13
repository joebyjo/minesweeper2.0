
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "CellMatrix.h"
#include "Cell.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace sf;
using namespace std;

class Game{

    protected:
        RenderWindow *game_window;
        CellMatrix *game_matrix;
        Clock game_timer;
        bool hasStarted;

    public:
        Game(int num_cols, int num_rows);
        void run();
        void mainMenu(sf::RenderWindow* window);
        bool play_animation();
        void append_highscore(string username,int score,int time_taken,string difficulty);
        bool check_game_win();

        // getters and setters
        RenderWindow* get_game_window();
        CellMatrix* get_game_matrix();
        
        void set_game_window(RenderWindow* game_window);
        void set_game_matrix(CellMatrix* game_matrix);

        ~Game();

        
};

#endif