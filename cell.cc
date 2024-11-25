#include "cell.h"
#include <stdexcept>

//ctor
Cell::Cell(char c = ' ', int life = -1): 
    c{c}, life{life} {}

int Cell::getLife() const{
    return life;
}

char Cell::getC() const{
    return c;
}

int Cell::getLevel() const{
    return level;
}