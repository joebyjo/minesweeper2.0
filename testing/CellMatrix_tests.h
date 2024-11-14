#ifndef CELLMATRIX_TESTS_H
#define CELLMATRIX_TESTS_H

#include "../Cell.h"
#include "../CellMatrix.h"
#include "../Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class CellMatrix_tests {

    public:
        void runTests() {
            test_constructor();            // Test 1: testing constructor now
            test_set_mine();               // Test 2: testing set mine function
            test_set_number();             // Test 3: testing set number function
            test_set_gameboard_display();  // Test 4: testing set_gameboard function and display function
        }

    private:
        void test_constructor() {
            CellMatrix matrix(5, 5, 0.3, nullptr);

            if(matrix.get_num_cols() == 5) {
                cout << "[*] Contructor test passed" << endl;
            }
        }

        void test_set_gameboard_display() {

            // setting the game
            Game test_game(5, 5);
            CellMatrix temp(5, 5, 0.3, test_game.get_game_window());
            test_game.set_game_matrix(&temp);
            CellMatrix* test = test_game.get_game_matrix();
            test->set_gameboard();

            // calling window and displaying and closing it
            test->display(test_game.get_game_window());  // checking display function
            test_game.get_game_window()->display();
            test_game.get_game_window()->close();

            cout << "[*] Display function test passed" << endl;
            cout << "[*] Set_gameboard function test passed" << endl;
        }

        void test_set_mine() {
            CellMatrix test(5, 5, 0.3, nullptr);
            test.set_mines();

            if(test.get_matrix()[test.get_mine_locations()[0]]->get_type() == "mine" &&
               test.get_matrix()[test.get_mine_locations()[test.get_num_mines() - 1]]->get_type() == "mine") {
                cout << "[*] set_mine test passed" << endl;
            } else {
                cout << "[*] set_mine test failed" << endl;
            }
        }

        void test_set_number() {
            CellMatrix test(10, 10, 0.3, nullptr);
            test.set_mines();
            test.set_numbers();

            int i = 0;
            while(true) {
                if(test.get_matrix()[test.get_mine_locations()[0] + i]->get_type() == "number") {
                    cout << "[*] set_number test passed" << endl;
                    break;
                } else if(test.get_matrix()[test.get_mine_locations()[0] + i]->get_type() != "mine") {
                    cout << "[*] set_mine test failed" << endl;
                }

                i++;
            }
        }
};
#endif