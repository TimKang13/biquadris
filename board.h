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
        void clear();
        // clear full rows
        int clearFullRows();
        void clearDeadCells();
        void collapseRows();
        void placeBlock(Block &b);
};

#endif