#ifndef GAME_TESTS_H
#define GAME_TESTS_H

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
        

        
};
#endif