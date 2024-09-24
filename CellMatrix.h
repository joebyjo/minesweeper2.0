#ifndef CELLMATRIX_H
#define CELLMATRIX_H

#include "Cell.h"

class CellMatrix{

    protected:
        Cell **matrix; // matrix to store pointers to cell
        int num_cols; // storing number of columns
        int num_rows; // storing number of rows

        int *mine_locations; // storing location of mines in one array
        int num_mines; // storing the number of mines

    public:
        CellMatrix(int num_rows, int num_cols);
        void display(RenderWindow *game_window);
        void set_gameboard(); // set the game board to the type of cell

        // getters and setters
        Cell** get_matrix();
        int get_num_cols();
        int get_num_rows();
        int get_num_mines();

        void set_matrix(Cell **matrix);
        void set_num_cols(int num_cols);
        void set_num_rows(int num_rows);
        void set_num_mines(int num_mines);


        ~CellMatrix();
        
};

#endif