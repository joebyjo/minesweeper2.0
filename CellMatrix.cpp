#include "CellMatrix.h"
#include "Constants.h"

CellMatrix::CellMatrix(int num_cols, int num_rows) {

    matrix = new Cell*[num_rows * num_cols]; // creating the 2-2 matrix of cells pointer

    // intiliasising each cells int the matrix
    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_cols; j++){

            matrix[i][j] = new Cell(i*CELL_SIZE, j*CELL_SIZE);
        }
    }
}