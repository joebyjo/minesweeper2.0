#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Cell{

    protected:
        RectangleShape *cell;
        int *location;
        Color color;
        bool is_reveal;


    public:
        Cell(int x, int y); // constructor

        void draw(RenderWindow *game_window); // drawing the object on window

        void set_color(Color color); // setting color

        void reveal(); // changing the color to the desiginated cell color

        void unique_function(); // owriting function

        
};

#endif