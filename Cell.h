#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

class Cell{

    protected:
        RectangleShape *cell;
        int *location;
        Color color;

    public:
        Cell(int x, int y); // constructor
        void draw(RenderWindow *game_window); // drawing the object on window
        

        // getters and setters 
        RectangleShape *get_cell();
        int *get_location();
        Color get_color();

        void set_cell(RectangleShape *cell);
        void set_location(int *location);
        void set_color(Color color);

        ~Cell();

        
};

#endif