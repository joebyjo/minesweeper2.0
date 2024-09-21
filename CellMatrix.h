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


        
};

#endif