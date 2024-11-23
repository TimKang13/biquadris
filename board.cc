#include "board.h"
#include "cell.h"
#include "block.h"
#include <stdexcept>
#include <iostream>
using namespace std;

const int EMPTY_LIFE = -1;

Board::Board():
    grid{8, std::vector<Cell>(11, Cell('d', EMPTY_LIFE))} {}

std::vector<std::vector<Cell>> Board::getGrid(){
    return grid;
}

bool Board::checkCollision(Block &b){

}

// clear full rows and dead cells and update grid
// return rows cleared
int Board::clear(){
    //clear full rows, return score?
    int rowsCleared = clearFullRows();
    // now clear dead cells


    return rowsCleared;
}

// clear full rows
int Board::clearFullRows(){

}

void Board::clearDeadCells(){

}

void Board::collapseRows(){
    
}

void Board::placeBlock(Block &b){

}



int main(){
    Board b {};
    cout << b.getGrid()[7][10].getC();
}
