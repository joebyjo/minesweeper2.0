#include <SFML/Graphics.hpp>
#include "Cell.h"
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

class Game{

    protected:
        RenderWindow *game_window;
        Cell *cell;

    public:
        Game(int size, string title);
        void run();

        
};