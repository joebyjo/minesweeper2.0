#include "CellMatrix_tests.h"
#include "Cell_tests.h"
#include "Game_tests.h"

int main() {

    // Cell Tests
    cout << "Cell Tests: " << endl;
    Cell_tests cell_test;
    cell_test.runTests();
    cout << "\n";

    // CellMatrix tests
    cout << "CellMatrix Tests: " << endl;
    CellMatrix_tests matrix_test;
    matrix_test.runTests();
    cout << "\n";

    // Game tests
    cout << "Game Tests: " << endl;
    Game_tests game_test;
    game_test.run_tests();

    return 0;
}