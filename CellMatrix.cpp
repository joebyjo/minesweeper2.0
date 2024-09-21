#include "CellMatrix.h"
#include "Constants.h"

CellMatrix::CellMatrix(int num_cols, int num_rows) {

    // updating value of matrix
    num_rows = this->num_rows;
    num_cols = this->num_cols;

    matrix = new Cell*[num_rows * num_cols]; // creating the 2-2 matrix of cells pointer

    // intiliasising each cells int the matrix
    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_cols; j++){

            matrix[i*num_cols + j] = new Cell(i*CELL_SIZE, j*CELL_SIZE);
            cout << i*CELL_SIZE << j*CELL_SIZE << endl;
        }
    }
}

void CellMatrix::display(RenderWindow *game_window) {
    for (int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_cols; j++){
            matrix[i*num_cols + j]->draw(game_window);
        }
    }
}
