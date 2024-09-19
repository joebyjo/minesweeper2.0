#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

class Game{

    protected:
        RenderWindow * game_matrix;

    public:
        Game(int size, string title);
        void run();

        
};