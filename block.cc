#include "block.h"
#include <stdexcept>

Block::Block(const Coordinate& pos): position{pos} {}

void Block::rotateMatrix(int degrees) {
    // Validate input
    if (degrees != 90 && degrees != -90) throw std::invalid_argument("Rotation must be either 90 or -90 degrees");
    // Create empty square matrix of the same size
    int length = shape.size();
    std::vector<std::vector<bool>> rotated(length, std::vector<bool>(length, false));
    // Rotate
    for (int oldRow = 0; oldRow < length; ++oldRow) {
        for (int oldCol = 0; oldCol < length; ++oldCol) {
            if (degrees == 90) {
                // Clockwise rotation (90 degrees)
                int newRow = oldCol;
                int newCol = length - oldRow - 1;
                rotated[newRow][newCol] = shape[oldRow][oldCol];
            } else if (degrees == -90) {
                // Counter-clockwise rotation (-90 degrees)
                int newRow = length - oldCol - 1;
                int newCol = oldRow;
                rotated[newRow][newCol] = shape[oldRow][oldCol];
            }
        }
    }

    // Copy rotated to shape 
    shape = rotated;
}

void Block::rotateCW() {
    rotateMatrix(90);
}

void Block::rotateCCW() {
    rotateMatrix(-90);
}

std::vector<Coordinate> Block::getAbsolutePositions() const {
    std::vector<Coordinate> positions;

    for (int row = 0; row < shape.size(); ++row) {
        for (int col = 0; col < shape[row].size(); ++col) {
            if (shape[row][col]) {
                positions.emplace_back(
                    position.row + row,
                    position.col + col
                );
            }
        }
    }
    return positions;
}

void Block::setPosition(const Coordinate& newPosition) {
    position = newPosition;
}

Coordinate Block::getPosition() const {
    return position;
}

const std::vector<std::vector<bool>>& Block::getShape() const {
    return shape;
}