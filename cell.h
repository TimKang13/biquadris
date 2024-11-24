#ifndef CELL_H
#define CELL_H
#include <vector>
#include <utility>

class Cell {
    char c;
    int life;
    public:
        Cell(char c, int life);
        int getLife() const;
        char getC() const;
};

#endif