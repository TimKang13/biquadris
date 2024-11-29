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
    std::vector<int> emptyLockers; 
    int rowsCleared;
    bool bonusEnabled;

    public:
        //ctor
        Board();
        //constants
        static const int WIDTH = 11;
        static const int HEIGHT = 18;
        //accessors
        std::vector<std::vector<Cell>> getGrid();
        char getCellChar(int row, int col) const {
            return grid[row][col].getC();
        }
        int getCellLife(int row, int col) const {
            return grid[row][col].getLife();
        }
        std::vector<CellLocker> getLockers() const{
            return lockers;
        }
        int getRowsCleared() const;
        //setters
        void enableBonus();
        //check if this block is colliding given 
        //current block position and current grid
        bool checkCollision(Block &b, bool checkRotatable = false);
        // clear full rows and dead cells
        int clear(int level);
        // clear full rows
        pair<int,int> clearFullRows();
        void clearDeadCells();
        void collapseRows();
        int placeBlock(Block &b, int level);
        void decrementCellLife();

        //for testing
        void printGrid();
        void setGrid(int r, int c, Cell cell);
        void setRowsCleared(int num);
};

#endif