#include "board.h"
#include "cell.h"
#include "block.h"
#include <stdexcept>
#include <iostream>
using namespace std;

const int EMPTY_LIFE = -1;
const Cell EMPTY_CELL = Cell(' ', EMPTY_LIFE);

Board::Board():
    grid{8, std::vector<Cell>(11, EMPTY_CELL)} {}

std::vector<std::vector<Cell>> Board::getGrid(){
    return grid;
}

//check if current position of the block collides
bool Board::checkCollision(Block &b){
    std::vector<Coordinate> positions = b.getAbsolutePositions();
    for(int i = 0; i < positions.size(); ++i){
        int row = positions[i].row;
        int col = positions[i].col;
        if(this->grid[row][col].getC() != ' '){
            return true;
        }
    }
    return false;
}

// clear full rows and dead cells and update grid
// return rows cleared
int Board::clear(){
    //clear full rows, return score?
    int rowsCleared = clearFullRows();
    // now clear dead cells
    clearDeadCells();
    // move everything down if cleared
    clearFullRows();
    return rowsCleared;
}

// clear full rows
int Board::clearFullRows(){
    int count = 0; 
    std::vector<Cell> emptyRow(grid[0].size(), EMPTY_CELL);

    for(int i = 0; i < this->grid.size(); ++i){
        bool isRowFull = true;
        for(int j = 0; j < this->grid[i].size(); ++j){
            if(this->grid[i][j].getC() == ' '){
                // not full row, break
                isRowFull = false;
                break;
            }
        }
        if(isRowFull){
            grid[i] = emptyRow;
            ++count;
        }
    }
    return count;
}

void Board::clearDeadCells(){
    for(int i = 0; i < this->grid.size(); ++i){
        for(int j = 0; j < this->grid[i].size(); ++j){
            this->grid[i][j] = EMPTY_CELL;
        }
    }
}

void Board::collapseRows(){
    std::vector<Cell> emptyRow(grid[0].size(), EMPTY_CELL);
    std::vector<int> emptyRows {};
    std::vector<int> nonEmptyRows {};

    for(int i = 0; i < this->grid.size(); ++i){
        bool isRowEmpty = true;
        for(int j = 0; j < this->grid[i].size(); ++j){
            if(this->grid[i][j].getC() != ' '){
                // not full row, break
                isRowEmpty = false;
                break;
            }
        }
        if(isRowEmpty){
            emptyRows.emplace_back(i);
        } else {
            nonEmptyRows.emplace_back(i);
        }
    }

    std::vector<std::vector<Cell>> tempGrid = this->grid;

    // [0, 1,2, 4, 6, 7]    [3, 5]
    // 
    // fill 6 with empty rows on top
    for(int i = 0; i < emptyRows.size(); ++i){
        this->grid[i] = emptyRow;
    }
    // fill with nonempty rows
    int p = 0;
    for(int i = emptyRows.size(); i < this->grid.size(); ++i){
        this->grid[i] = tempGrid[nonEmptyRows[p]];
        ++p;
    }
}

//place block if no collision, do nothing if collision 
void Board::placeBlock(Block &b){
    if(!checkCollision(b)){
        // char c = b.getCharacter();
        char c = 'j';
        std::vector<Coordinate> positions = b.getAbsolutePositions();
        for(int i = 0; i < positions.size(); ++i){
            int row = positions[i].row;
            int col = positions[i].col;
            this->grid[row][col] = Cell(c, 10); // 10 for now, will have to implement logic
        }
    }
}

//for testing
void Board::printGrid() {
    cout << "   "; // Add spacing for the column indices
    for (int col = 0; col < grid[0].size(); ++col) {
        cout << col << " ";
    }
    cout << endl;

    for (int row = 0; row < grid.size(); ++row) {
        cout << row << " "; // Print the row index
        if (row < 10) cout << " "; // Adjust spacing for single-digit row indices
        for (const auto& cell : grid[row]) {
            cout << cell.getC() << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void Board::setGrid(int r, int c, Cell cell){
    grid[r][c] = cell;
}

int main() {
    Board b {};

    b.printGrid();

    // Place a JBlock at position (6, 6)
    JBlock jBlock(Coordinate{6, 6});
    cout << b.checkCollision(jBlock);
    b.placeBlock(jBlock);

    cout << "Board after placing JBlock at (6, 6):" << endl;
    b.printGrid();
    // Test setGrid: Manually fill some cells
    cout << "Setting cells on row 7 to simulate a filled row:" << endl;
    for (int col = 0; col < 11; ++col) {
        b.setGrid(7, col, Cell('x', 10)); // Fill row 7
    }
    b.printGrid();

    // Test clearFullRows: Clear the fully filled row
    cout << "Clearing full rows:" << endl;
    int rowsCleared = b.clearFullRows();
    cout << "Rows Cleared: " << rowsCleared << endl;
    b.printGrid();

    // Test setGrid and collapseRows: Add scattered blocks and collapse rows
    cout << "Setting scattered cells to test row collapsing:" << endl;
    b.setGrid(6, 0, Cell('o', 10));
    b.setGrid(5, 1, Cell('o', 10));
    b.setGrid(4, 2, Cell('o', 10));
    b.printGrid();

    cout << "Collapsing rows:" << endl;
    b.collapseRows();
    b.printGrid();

    // Test collision detection
    cout << "Testing collision detection for a IBlock at (6, 6):" << endl;
    IBlock iBlock(Coordinate{6, 6});
    cout << "Collision detected: " << (b.checkCollision(iBlock) ? "Yes" : "No") << endl;

    // Test placing a block with no collision
    cout << "Placing IBlock at (6, 6):" << endl;
    b.placeBlock(iBlock);
    b.printGrid();

        // Test collision detection
    cout << "Testing collision detection for a IBlock at (7, 3):" << endl;
    iBlock = IBlock{Coordinate{7,3}};
    cout << "Collision detected: " << (b.checkCollision(iBlock) ? "Yes" : "No") << endl;

    // Test clearing all cells
    cout << "Clearing all cells:" << endl;
    b.clearDeadCells();
    b.printGrid();

    return 0;
}