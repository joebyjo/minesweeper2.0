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
        void set_color(Color color);

        
};