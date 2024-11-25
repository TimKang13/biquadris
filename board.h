#ifndef BOARD_H
#define BOARD_H
#include "block.h"
#include "cell.h"
#include <vector>
#include <utility>

class Board {
    // current board 
    std::vector<std::vector<Cell>> grid;
    // std::vector< cabinet;
    // int emptyCabinetIndex;

    public:
        //ctor
        Board();
        //accessors
        std::vector<std::vector<Cell>> getGrid();


        //check if this block is colliding given 
        //current block position and current grid
        bool checkCollision(Block &b);
        // clear full rows and dead cells
        int clear(int level);
        // clear full rows
        int clearFullRows();
        int clearDeadCells();
        void collapseRows();
        int placeBlock(Block &b, int level);

        char getCell(int row, int col) const {
            return grid[row][col].getC();
        }

        //for testing
        void printGrid();
        void setGrid(int r, int c, Cell cell);
};

#endif