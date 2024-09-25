#include <cstdlib>

#include "CellMatrix.h"
#include "Constants.h"
#include "Cell.h"
#include "Mine.h"
#include "Empty.h"
#include "Number.h"

CellMatrix::CellMatrix(int num_rows, int num_cols) {

    // updating value of matrix
    this->num_rows = num_rows;
    this->num_cols = num_cols;

    // creating the 2D array of cells pointer
    matrix = new Cell*[num_rows * num_cols]; 

    num_mines = NUM_OF_MINES;

    // creating array to store location of mines
    mine_locations = new int[num_mines];

    // initialising initially with nullptr
    for (int i = 0; i < num_rows*num_cols; i++) {
            matrix[i] = nullptr;
    }

}

void CellMatrix::display(RenderWindow *game_window) {
    for (int i = 0; i < num_rows*num_cols; i++) {
            matrix[i]->draw(game_window);  
    }
}

void CellMatrix::set_gameboard() {
    srand(RANDOM_SEED);

    auto check_if_member = [&](int num) {
        for (int i = 0; i < num_mines; ++i) {
            if (mine_locations[i] == num) {
                return true;
            }
        }
        return false;
    };

    // initialising all mines into the matrix randomly
    for (int i=0; i< num_mines; i++) {
        int location = rand() % (num_rows * num_cols);

        if (!(check_if_member(location))) { mine_locations[i] = location;} 
        else { i--; };

        int col = location % num_cols;
        int row = location / num_cols;

        matrix[location] = new Mine(col, row);
        
    }

    // initialising each cells into the matrix
    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_cols; j++){   
        
            // initialising all non-mine elements of matrix with Cell()
            if (matrix[i*num_cols + j] == nullptr){
                matrix[i*num_cols + j] = new Empty(j, i);
                // std::cout << "O ";
            } else {
                // std::cout << "X ";
            }
        }
        // std::cout << std::endl;
    }
    
    display_overlay();

}

void CellMatrix::display_overlay() {
    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_cols; j++){
            // alternating colors
            if (((j%2== 0) && (i%2==0)) || ((j%2==1) && (i%2==1))){ 
                matrix[i*num_cols + j]->set_color(CELL_COLOR_2); } 
            else { 
                matrix[i*num_cols + j]->set_color(CELL_COLOR_1); } 
        }
    }

}

// game over function
void CellMatrix::game_over() {}

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

// get num mines
int CellMatrix::get_num_mines() { 
    return this->num_mines; 
}

int* CellMatrix::get_mine_locations() {
    return this->mine_locations;
}

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

// set mine locations
void CellMatrix::set_mine_locations(int *mine_locations) {
    this->mine_locations = mine_locations;
}

// destroy cells and cell matrix
CellMatrix:: ~CellMatrix() {

    for (int i = 0; i < num_rows*num_cols; i++){
        delete matrix[i];
    }

    delete[] matrix;
    delete[] mine_locations;

}