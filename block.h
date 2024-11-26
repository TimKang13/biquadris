#ifndef BLOCK_H
#define BLOCK_H
#include <vector>
#include <utility>
using namespace std;


struct Coordinate {
    int row, col;
    Coordinate(int r = 0, int c = 0): row{r}, col{c} {}
};

class Block {
    protected:
        // Position of block's bottom-left
        Coordinate position;
        // Shape matrix representing filled cells
        std::vector<std::vector<bool>> shape;
        // Character used to represent filled cells
        char fill;
        // Helper functions
        void rotateMatrix(int degrees);
    public:
        Block(const Coordinate& pos = {0, 0}, char fill = '#');
        virtual ~Block() = default;
        // Rotates the block 90 degrees clockwise
        void rotateCW();
        // Rotates the block 90 degrees counter-clockwise
        void rotateCCW();
        // Returns vector of absolute coordinates of all filled cells
        std::vector<Coordinate> getAbsolutePositions() const;
        // Getters and setters
        Coordinate getPosition() const;
        void setPosition(const Coordinate& newPos);
        const std::vector<std::vector<bool>>& getShape() const;
        char getFill() const;
};

class IBlock : public Block {
    public:
        IBlock(const Coordinate& pos = {0, 0}) : Block{pos, 'I'} {
            shape = {
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0},
                {1,1,1,1}
            };
        }
};

class JBlock : public Block {
    public:
        JBlock(const Coordinate& pos = {0, 0}) : Block{pos, 'J'} {
            shape = {
                {0,0,0},
                {1,0,0},
                {1,1,1}
            };
        }
};

class LBlock : public Block {
    public:
        LBlock(const Coordinate& pos = {0, 0}) : Block{pos, 'L'} {
            shape = {
                {0,0,0},
                {0,0,1},
                {1,1,1}
            };
        }
};

class OBlock : public Block {
    public:
        OBlock(const Coordinate& pos = {0, 0}) : Block{pos, 'O'} {
            shape = {
                {1,1},
                {1,1}
            };
        }
};

class SBlock : public Block {
    public:
        SBlock(const Coordinate& pos = {0, 0}) : Block{pos, 'S'} {
            shape = {
                {0,0,0},
                {0,1,1},
                {1,1,0}
            };
        }
};

class ZBlock : public Block {
    public:
        ZBlock(const Coordinate& pos = {0, 0}) : Block{pos, 'Z'} {
            shape = {
                {0,0,0},
                {1,1,0},
                {0,1,1}
            };
        }
};

class TBlock : public Block {
    public:
        TBlock(const Coordinate& pos = {0, 0}) : Block{pos, 'T'} {
            shape = {
                {0,0,0},
                {1,1,1},
                {0,1,0}
            };
        }
};
#endif