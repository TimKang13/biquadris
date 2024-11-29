#ifndef CELL_H
#define CELL_H
#include <vector>
#include <utility>

class Cell {
    char c;
    int life;
    bool invincible;
    int level;
    int lockerID;
    public:
        Cell(char c = ' ', int life = -1, bool invincible = true, int level = 0, int lockerID = 0);  //Cell really shouldn't have a default ctor...
        void setLife(int newLife);
        int getLife() const;
        char getC() const;
        int getLevel() const;
        int getLockerID() const;
        bool isInvincible() const;
};

#endif
