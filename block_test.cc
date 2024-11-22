#include "block.h"
#include <iostream>

void printBlock(const Block& block) {
    std::cout << "Position: (" << block.getPosition().row << "," 
              << block.getPosition().col << ")\n";
    // Print shape
    for (size_t i = 0; const auto& row : block.getShape()) {
        for (bool cell : row) {
            std::cout << (cell ? block.getFill() : '.');
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

int main() {
    JBlock j{{0,0}};  // J block at origin
    
    std::cout << "Initial J block:\n";
    printBlock(j);
    for (const auto& pos : j.getAbsolutePositions()) {
        std::cout << "(" << pos.row << "," << pos.col << ")";
    }
    
    std::cout << "\nAfter rotating clockwise:\n";
    j.rotateCW();
    printBlock(j);
    
    std::cout << "After moving to (2,3):\n";
    j.setPosition({2,3});
    printBlock(j);
    
    std::cout << "Absolute positions:\n";
    for (const auto& pos : j.getAbsolutePositions()) {
        std::cout << "(" << pos.row << "," << pos.col << ") ";
    }
    std::cout << "\n\n";
}