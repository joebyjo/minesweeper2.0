#ifndef CELL_TESTS_H
#define CELL_TESTS_H

#include <iostream>
#include "../Cell.h"
#include "../Empty.h"
#include "../CellMatrix.h"
#include "../Game.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Cell_tests {
    
    public:
        void runTests() {
            // test_constructor(); // Test 1: testing constructor now, cannot be tested as an abstract class
            test_draw();// Test 2: Checking draw() function
            test_reveal(); // Test 3: reavealig one cell and testing reaveal function
            test_flag(); // Test 4: flaging the cell
            test_set_and_get_color(); // Test 6: s=Setting the color of the cell maually
        }

    private:
        // void test_constructor() {

        //     Cell cell(5, 10);
        //     // Check if the location is set correctly
        //     if (cell.get_location()[0] != 5 || cell.get_location()[1] != 10) {
        //         std::cout << "Constructor test failed!" << std::endl;
        //     } else {
        //         std::cout << "Constructor test passed!" << std::endl;
        //     }
        // }

        void test_draw(){
            RenderWindow test(VideoMode(50 * 1, 50 * 1), "Cell Test");
            Empty cell(0, 0);  // if the screen appears then draw() worked as well
            cell.draw(&test);
            test.display();
            test.close();
            
            cout << "[*] Draw Test Passed" << endl;
        }

        void test_set_and_get_color() {
                Game test(5, 5);
                CellMatrix temp(5, 5, 0.3, test.get_game_window());
                test.set_game_matrix(&temp);
                test.get_game_matrix()->set_gameboard();
                Cell* cell = test.get_game_matrix()->get_matrix()[0];
                cell->set_color(Color:: Red);

                while(test.get_game_window()->isOpen()){
                test.get_game_matrix()->display(test.get_game_window());
                test.get_game_window()->display();

                string results;
                cout << "Is the color red on matrix location 0,0 (Y/N): ";
                cin >> results;

                if (results == "Y" || results == "y"){
                    cout << "[*] Get/Set Color Test passed" << endl;
                    test.get_game_window()->close();
                } else{
                    cout << "[*] Get/Set Color Test failed" << endl;
                    test.get_game_window()->close();
                }

                // Checking if the color is set correctly
                // if the color of the first cell becomes red then test passed
            }
        }

        void test_reveal() {

            CellMatrix test(5, 5, 0.3, nullptr);
            test.set_gameboard();
            Cell* cell = test.get_matrix()[0];
            cell->reveal(&test);

            // Check if the cell was revealed
            if (!cell->get_is_reveal()) { // check on the matrix if the cell has been revealed
                std::cout << "[*] Reveal test failed!" << std::endl;
            } else {
                std::cout << "[*] Reveal test passed!" << std::endl;
            }
        }

        void test_flag() {

            Game test(5, 5);
            CellMatrix temp(5, 5, 0.3, test.get_game_window());
            test.set_game_matrix(&temp);
            test.get_game_matrix()->set_gameboard();
            Cell* cell = test.get_game_matrix()->get_matrix()[0];

            test.get_game_matrix()->display(test.get_game_window());
            test.get_game_window()->display();

            cell->flag(test.get_game_window());

            // Checkinf if the flag is set correctly
            if (!cell->get_is_flagged()) {
                std::cout << "[*] Flag test failed!" << std::endl;
            } else {
                std::cout << "[*] Flag test passed!" << std::endl;
            }

            cell->flag(test.get_game_window());

            // Checking if the flag is removed
            if (cell->get_is_flagged()) {
                std::cout << "[*] Flag removal test failed!" << std::endl;
            } else {
                std::cout << "[*] Flag removal test passed!" << std::endl;
            }

            // checking if lets reveal a flagged cell
            cell->flag(test.get_game_window());
            cell->reveal(test.get_game_matrix());
            if (cell->get_is_reveal()) {
                std::cout << "[*] Revealing a flaged cell test failed!" << std::endl;
            } else {
                std::cout << "[*] Revealiing a flagged cell passed" << std::endl;
            }

            // checking if it lets flag a revealed cell
            cell->reveal(test.get_game_matrix());
            cell->flag(test.get_game_window());
            if (cell->get_is_flagged()) {
                std::cout << "[*] Not flaging a reveal cell failed!" << std::endl;
            } else {
                std::cout << "[*] Not flaging a revealed cell test passed!" << std::endl;
            }

            test.get_game_window()->close();
        }
};
#endif