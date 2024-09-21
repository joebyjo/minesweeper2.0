#ifndef CELLMATRIX_H
#define CELLMATRIX_H

#include "Cell.h"

class CellMatrix{

    protected:
        Cell **matrix;
        int num_cols;
        int num_rows;

    public:
        CellMatrix(int num_cols, int num_rows);
        void display(RenderWindow *game_window);


        
};

#endif