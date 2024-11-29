#include "cell.h"
#include <stdexcept>

//ctor
Cell::Cell(char c, int life, bool invincible, int level, int lockerID): 
    c{c}, life{life}, level{level}, invincible{invincible}, lockerID{lockerID} {}

void Cell::setLife(int newLife) {
    life = newLife;
}

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

bool Cell::isInvincible() const {
    return invincible;
}
