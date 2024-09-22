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

void CellMatrix::set_gameboard() {
    
}

// get matrix
Cell** CellMatrix:: get_matrix() {
    return this->matrix;
}

// get num cols
int CellMatrix:: get_num_cols() {
    return this->num_cols;
}

// get num rows
int CellMatrix:: get_num_rows() {
    return this->num_rows;
}

int CellMatrix::get_num_mines() { return this->num_mines; }

// set matrix manually
void CellMatrix:: set_matrix(Cell **matrix) {
    this->matrix = matrix;
};

// set num of cols manually
void CellMatrix:: set_num_cols(int num_cols){
    this->num_cols = num_cols;
};

// set num of rows manually
void CellMatrix:: set_num_rows(int num_rows){
    this->num_rows = num_rows;
}

// set num of mines
void CellMatrix::set_num_mines(int num_mines) {
    this->num_mines = num_mines;
}

// destroy cells and cell matrix
CellMatrix:: ~CellMatrix() {

    for (int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_cols; j++){
            delete matrix[i*num_cols + j];
        }
    }

    delete[] matrix;

}