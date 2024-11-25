#ifndef CELL_H
#define CELL_H
#include <vector>
#include <utility>

class Cell {
    char c;
    int life;
    int level;
    int lockerID;
    public:
        Cell(char c = ' ', int life = -1, int level = 0, int lockerID);
        int getLife() const;
        char getC() const;
        int getLevel() const;
        int getLockerID() const;
};

#endif