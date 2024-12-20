#include "block.h"
#include <stdexcept>
using namespace std;


Block::Block(const Coordinate& pos, char fill, int life, bool invincible, bool heavy): 
    position{pos}, fill{fill}, life{life}, invincible{invincible}, heavy{heavy} {}

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

std::vector<Coordinate> Block::getAbsolutePositions(bool filledOnly) const {
    std::vector<Coordinate> positions;
    for (int row = 0; row < shape.size(); ++row) {
        int relativeRow = shape.size() - row - 1; // Convert row index to bottom-left origin
        for (int col = 0; col < shape[row].size(); ++col) {
            if (filledOnly && !shape[row][col]) {
                continue;
            }
            positions.emplace_back(
                position.row - relativeRow,
                position.col + col
            );
        }
    }
    return positions;
}

void Block::setPosition(const Coordinate& newPosition) {
    position = newPosition;
}
void Block::setHeavy(bool input) {heavy = input;}
Coordinate Block::getPosition() const {
    return position;
}

const std::vector<std::vector<bool>>& Block::getShape() const {
    return shape;
}

char Block::getFill() const {
    return fill;
}

int Block::getLife() const { return life;}
bool Block::isInvincible() const {return invincible;}
bool Block::isHeavy() const {return heavy;}
