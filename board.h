#ifndef BOARD_H
#define BOARD_H
#include "block.h"
#include "cell.h"
#include <vector>
#include <utility>

struct CellLocker {
    int count;
    char c;
    int level;
};

class Board {
    // current board 
    std::vector<std::vector<Cell>> grid;
    std::vector<CellLocker> lockers;
    int emptyLocker; //-1 if all full . then emplace back

    public:
        //ctor
        Board();
        //constants
        static const int WIDTH = 11;
        static const int HEIGHT = 15;
        //accessors
        std::vector<std::vector<Cell>> getGrid();
        char getCell(int row, int col) const {
            return grid[row][col].getC();
        }
        //check if this block is colliding given 
        //current block position and current grid
        bool checkCollision(Block &b);
        // clear full rows and dead cells
        int clear(int level);
        // clear full rows
        pair<int,int> clearFullRows();
        int clearDeadCells();
        void collapseRows();
        int placeBlock(Block &b, int level);

        //for testing
        void printGrid();
        void setGrid(int r, int c, Cell cell);
};

#endif