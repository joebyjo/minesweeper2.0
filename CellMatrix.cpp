#include "CellMatrix.h"
#include "Constants.h"

CellMatrix::CellMatrix(int num_rows, int num_cols) {

    // updating value of matrix
    this->num_rows = num_rows;
    this->num_cols = num_cols;

    // creating the 2 x 2 matrix of cells pointer
    matrix = new Cell*[num_rows * num_cols]; 

    // initialising each cells into the matrix
    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_cols; j++){

            matrix[i*num_cols + j] = new Cell(j*CELL_SIZE, i*CELL_SIZE);

            // alternating colors
            if ((j%2== 0) && (i%2==0)){
                matrix[i*num_cols + j]->set_color(CELL_COLOR_2);
            } else if ((j%2==1) && (i%2==1)) {
                matrix[i*num_cols + j]->set_color(CELL_COLOR_2);

            }
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
