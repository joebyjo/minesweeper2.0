#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

class CellMatrix;

class Cell{

    protected:
        RectangleShape *cell;
        int *location;
        Color color;
        bool is_reveal;
        string type;

    public:
        Cell(int x, int y); // constructor

        virtual void draw(RenderWindow *game_window); // drawing the object on window
        virtual void reveal(CellMatrix *game_matrix); // changing the color to the desiginated cell color
        virtual void on_revealed(CellMatrix *game_matrix) = 0; // owriting function
        

        // getters and setters 
        RectangleShape *get_cell();
        int *get_location();
        Color get_color();
        string get_type();

        void set_cell(RectangleShape *cell);
        void set_location(int *location);
        void set_color(Color color);

        virtual ~Cell();

        
};

#endif