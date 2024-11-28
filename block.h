#ifndef BLOCK_H
#define BLOCK_H
#include <vector>
#include <utility>
#include <iostream>
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
        int life;
        bool invincible;
        bool heavy;
    public:
        Block(const Coordinate& pos = {0, 0}, char fill = '#', int life = -1, bool invincible = true, bool heavy = false);
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
        void setHeavy(bool in);
        const std::vector<std::vector<bool>>& getShape() const;
        char getFill() const;
        int getLife() const;
        bool isInvincible() const;
        bool isHeavy() const;
};

class IBlock : public Block {
    public:
        IBlock(const Coordinate& pos = {3, 0}, int life = -1, bool invincible = true) : Block{pos, 'I', life, invincible} {
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
        JBlock(const Coordinate& pos = {3, 0}, int life = -1, bool invincible = true) : Block{pos, 'J', life, invincible} {
            shape = {
                {0,0,0},
                {1,0,0},
                {1,1,1}
            };
        }
};

class LBlock : public Block {
    public:
        LBlock(const Coordinate& pos = {3, 0}, int life = -1, bool invincible = true) : Block{pos, 'L', life, invincible} {
            shape = {
                {0,0,0},
                {0,0,1},
                {1,1,1}
            };
        }
};

class OBlock : public Block {
    public:
        OBlock(const Coordinate& pos = {3, 0}, int life = -1, bool invincible = true) : Block{pos, 'O', life, invincible} {
            shape = {
                {1,1},
                {1,1}
            };
        }
};

class SBlock : public Block {
    public:
        SBlock(const Coordinate& pos = {3, 0}, int life = -1, bool invincible = true) : Block{pos, 'S', life, invincible} {
            shape = {
                {0,0,0},
                {0,1,1},
                {1,1,0}
            };
        }
};

class ZBlock : public Block {
    public:
        ZBlock(const Coordinate& pos = {3, 0}, int life = -1, bool invincible = true) : Block{pos, 'Z', life, invincible} {
            shape = {
                {0,0,0},
                {1,1,0},
                {0,1,1}
            };
        }
};

class TBlock : public Block {
    public:
        TBlock(const Coordinate& pos = {3, 0}, int life = -1, bool invincible = true) : Block{pos, 'T', life, invincible} {
            shape = {
                {0,0,0},
                {1,1,1},
                {0,1,0}
            };
        }
};

class OneBlock : public Block {
    public:
        OneBlock(const Coordinate& pos = {3, 5}, int life = -1, bool invincible = true) : Block{pos, '*', life, invincible} {
            shape = {{1}};
        }
};
#endif