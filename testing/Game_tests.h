#ifndef GAME_TESTS_H
#define GAME_TESTS_h

#include <iostream>
#include "../Cell.h"
#include "../CellMatrix.h"
#include "../Game.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Game_tests {
    
    public:
        void run_tests() {
            test_constructor(); // Test 1: testing constructor now
            apply_routine(); // Testing by appying routine on the game
        }

    private:
        void test_constructor(){
            Game test(5, 5);
            
            if (test.get_game_window() == nullptr){
                cout << "[*] Constructor test failed" << endl;
            } else {
                cout << "[*] Constructor test passed" << endl;
            }
        }

        void apply_routine(){
            cout << "Apply routine: " << endl;
            Game minesweeper(5, 5);
            minesweeper.main_menu(minesweeper.get_game_window());
        }
        

        
};
#endif