#ifndef CELLMATRIX_H
#define CELLMATRIX_H

#include "Cell.h"

class CellMatrix{

    protected:
        Cell **matrix;
        int num_cols;
        int num_rows;

    public:
        CellMatrix(int num_rows, int num_cols);
        void display(RenderWindow *game_window);

        // getters and setters
        Cell** get_matrix();
        int get_num_cols();
        int get_num_rows();

        void set_matrix(Cell **matrix);
        void set_num_cols(int num_cols);
        void set_num_rows(int num_rows);


        ~CellMatrix();
        
};

#endif