#ifndef BOARD_H
#define BOARD_H
#include "block.h"
#include "cell.h"
#include <vector>
#include <utility>

class Board {
    // current board 
    std::vector<std::vector<Cell>> grid;

    public:
        //ctor
        Board();
        //accessors
        std::vector<std::vector<Cell>> getGrid();


        //check if this block is colliding given 
        //current block position and current grid
        bool checkCollision(Block &b);
        // clear full rows and dead cells
        int clear();
        // clear full rows
        int clearFullRows();
        void clearDeadCells();
        void collapseRows();
        void placeBlock(Block &b);

        char getCell(int row, int col) const {
            return grid[row][col].getC();
        }

        //for testing
        void printGrid();
        void setGrid(int r, int c, Cell cell);
};

#endif