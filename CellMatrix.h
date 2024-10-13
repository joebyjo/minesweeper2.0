#ifndef CELLMATRIX_H
#define CELLMATRIX_H

#include <vector>

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Cell;

class CellMatrix{

    protected:
        Cell **matrix; // matrix to store pointers to cell
        int num_cols; // storing number of columns
        int num_rows; // storing number of rows

        vector<int> mine_locations; // storing location of mines in one array
        int num_mines; // storing the number of mines
        int revealed_cells;
        bool is_gameover;
        RenderWindow *game_window;

    public:
        CellMatrix(int num_rows, int num_cols, RenderWindow *game_window);
        void display(RenderWindow *game_window);

        void set_gameboard(); // set the game board to the type of cell
        void set_mines(); // setting mines
        void set_numbers(); // setting numbers cell
        void set_empty_cells(); // setting empty cells
        void set_powerups(); // setting powerups 
        void display_overlay(); // displays the overlaying checkerboard
        
        void reveal_all_cells(); // reveals all the cells (used for development)
        void increment_revealed();
        void game_over();
        void first_click(int cell_index_x, int cell_index_y); // changing the gameboard based on first click

        // getters and setters
        Cell** get_matrix();
        int get_num_cols();
        int get_num_rows();
        int get_num_mines();
        vector<int> get_mine_locations();
        RenderWindow *get_game_window();
        int get_revealed_cells();
        bool get_gameover();


        void set_matrix(Cell **matrix);
        void set_num_cols(int num_cols);
        void set_num_rows(int num_rows);
        void set_num_mines(int num_mines);
        void set_mine_locations(vector<int> mine_locations);
        void set_gameover(bool state);
        void set_game_window(RenderWindow* game_window);


        ~CellMatrix();
        
};

#endif