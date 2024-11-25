#include "cell.h"
#include <stdexcept>

//ctor
Cell::Cell(char c, int life, int level, int lockerID): 
    c{c}, life{life}, level{level}, lockerID{lockerID} {}

int Cell::getLife() const{
    return life;
}

char Cell::getC() const{
    return c;
}

int Cell::getLevel() const{
    return level;
}

int Cell::getLockerID() const {
    return lockerID;
}